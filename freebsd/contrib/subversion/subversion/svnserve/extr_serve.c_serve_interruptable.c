#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_8__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ cmdname; } ;
typedef  TYPE_1__ svn_ra_svn__cmd_entry_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
struct TYPE_10__ {int /*<<< orphan*/  conn; int /*<<< orphan*/  baton; TYPE_8__* params; int /*<<< orphan*/  pool; int /*<<< orphan*/  usock; } ;
typedef  TYPE_2__ connection_t ;
typedef  scalar_t__ apr_status_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
struct TYPE_11__ {int /*<<< orphan*/  max_response_size; int /*<<< orphan*/  max_request_size; int /*<<< orphan*/  error_check_interval; int /*<<< orphan*/  zero_copy_limit; int /*<<< orphan*/  compression_level; } ;

/* Variables and functions */
 int /*<<< orphan*/  APR_SO_KEEPALIVE ; 
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 scalar_t__ apr_socket_opt_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * construct_server_baton (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_8__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* main_commands ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,scalar_t__,TYPE_1__ const*) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_ra_svn__handle_command (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_ra_svn__has_command (scalar_t__*,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_svn_create_conn5 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

svn_error_t *
serve_interruptable(svn_boolean_t *terminate_p,
                    connection_t *connection,
                    svn_boolean_t (* is_busy)(connection_t *),
                    apr_pool_t *pool)
{
  svn_boolean_t terminate = FALSE;
  svn_error_t *err = NULL;
  const svn_ra_svn__cmd_entry_t *command;
  apr_pool_t *iterpool = svn_pool_create(pool);

  /* Prepare command parser. */
  apr_hash_t *cmd_hash = apr_hash_make(pool);
  for (command = main_commands; command->cmdname; command++)
    svn_hash_sets(cmd_hash, command->cmdname, command);

  /* Auto-initialize connection */
  if (! connection->conn)
    {
      apr_status_t ar;

      /* Enable TCP keep-alives on the socket so we time out when
       * the connection breaks due to network-layer problems.
       * If the peer has dropped the connection due to a network partition
       * or a crash, or if the peer no longer considers the connection
       * valid because we are behind a NAT and our public IP has changed,
       * it will respond to the keep-alive probe with a RST instead of an
       * acknowledgment segment, which will cause svn to abort the session
       * even while it is currently blocked waiting for data from the peer. */
      ar = apr_socket_opt_set(connection->usock, APR_SO_KEEPALIVE, 1);
      if (ar)
        {
          /* It's not a fatal error if we cannot enable keep-alives. */
        }

      /* create the connection, configure ports etc. */
      connection->conn
        = svn_ra_svn_create_conn5(connection->usock, NULL, NULL,
                                  connection->params->compression_level,
                                  connection->params->zero_copy_limit,
                                  connection->params->error_check_interval,
                                  connection->params->max_request_size,
                                  connection->params->max_response_size,
                                  connection->pool);

      /* Construct server baton and open the repository for the first time. */
      err = construct_server_baton(&connection->baton, connection->conn,
                                   connection->params, pool);
    }

  /* If we can't access the repo for some reason, end this connection. */
  if (err)
    terminate = TRUE;

  /* Process incoming commands. */
  while (!terminate && !err)
    {
      svn_pool_clear(iterpool);
      if (is_busy && is_busy(connection))
        {
          svn_boolean_t has_command;

          /* If the server is busy, execute just one command and only if
           * there is one currently waiting in our receive buffers.
           */
          err = svn_ra_svn__has_command(&has_command, &terminate,
                                        connection->conn, iterpool);
          if (!err && has_command)
            err = svn_ra_svn__handle_command(&terminate, cmd_hash,
                                             connection->baton,
                                             connection->conn,
                                             FALSE, iterpool);

          break;
        }
      else
        {
          /* The server is not busy, thus let's serve whichever command
           * comes in next and whenever it comes in.  This requires the
           * busy() callback test to return TRUE while there are still some
           * resources left.
           */
          err = svn_ra_svn__handle_command(&terminate, cmd_hash,
                                           connection->baton,
                                           connection->conn,
                                           FALSE, iterpool);
        }
    }

  /* error or normal end of session. Close the connection */
  svn_pool_destroy(iterpool);
  if (terminate_p)
    *terminate_p = terminate;

  return svn_error_trace(err);
}
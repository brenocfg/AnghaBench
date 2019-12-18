#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_2__ trail_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct read_rep_args {scalar_t__* len; TYPE_1__* rb; int /*<<< orphan*/  buf; } ;
struct TYPE_10__ {scalar_t__ sha1_checksum; scalar_t__ md5_checksum; } ;
typedef  TYPE_3__ representation_t ;
struct TYPE_8__ {scalar_t__ offset; scalar_t__ size; scalar_t__ rep_key; int /*<<< orphan*/  sha1_checksum; int /*<<< orphan*/  md5_checksum; int /*<<< orphan*/  fs; scalar_t__ checksum_finalized; int /*<<< orphan*/  sha1_checksum_ctx; int /*<<< orphan*/  md5_checksum_ctx; int /*<<< orphan*/  scratch_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_CORRUPT ; 
 int /*<<< orphan*/  SVN_ERR_FS_REP_CHANGED ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/ * _ (char*) ; 
 int /*<<< orphan*/  rep_read_range (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_checksum_final (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_checksum_match (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_checksum_mismatch_err (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  svn_checksum_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_bdb__read_rep (TYPE_3__**,int /*<<< orphan*/ ,scalar_t__,TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
txn_body_read_rep(void *baton, trail_t *trail)
{
  struct read_rep_args *args = baton;

  if (args->rb->rep_key)
    {
      SVN_ERR(rep_read_range(args->rb->fs,
                             args->rb->rep_key,
                             args->rb->offset,
                             args->buf,
                             args->len,
                             trail,
                             args->rb->scratch_pool));

      args->rb->offset += *(args->len);

      /* We calculate the checksum just once, the moment we see the
       * last byte of data.  But we can't assume there was a short
       * read.  The caller may have known the length of the data and
       * requested exactly that amount, so there would never be a
       * short read.  (That's why the read baton has to know the
       * length of the data in advance.)
       *
       * On the other hand, some callers invoke the stream reader in a
       * loop whose termination condition is that the read returned
       * zero bytes of data -- which usually results in the read
       * function being called one more time *after* the call that got
       * a short read (indicating end-of-stream).
       *
       * The conditions below ensure that we compare checksums even
       * when there is no short read associated with the last byte of
       * data, while also ensuring that it's harmless to repeatedly
       * read 0 bytes from the stream.
       */
      if (! args->rb->checksum_finalized)
        {
          SVN_ERR(svn_checksum_update(args->rb->md5_checksum_ctx, args->buf,
                                      *(args->len)));
          SVN_ERR(svn_checksum_update(args->rb->sha1_checksum_ctx, args->buf,
                                      *(args->len)));

          if (args->rb->offset == args->rb->size)
            {
              representation_t *rep;

              SVN_ERR(svn_checksum_final(&args->rb->md5_checksum,
                                         args->rb->md5_checksum_ctx,
                                         trail->pool));
              SVN_ERR(svn_checksum_final(&args->rb->sha1_checksum,
                                         args->rb->sha1_checksum_ctx,
                                         trail->pool));
              args->rb->checksum_finalized = TRUE;

              SVN_ERR(svn_fs_bdb__read_rep(&rep, args->rb->fs,
                                           args->rb->rep_key,
                                           trail, trail->pool));

              if (rep->md5_checksum
                  && (! svn_checksum_match(rep->md5_checksum,
                                           args->rb->md5_checksum)))
                return svn_error_create(SVN_ERR_FS_CORRUPT,
                        svn_checksum_mismatch_err(rep->md5_checksum,
                             args->rb->md5_checksum, trail->pool,
                             _("MD5 checksum mismatch on representation '%s'"),
                             args->rb->rep_key),
                        NULL);

              if (rep->sha1_checksum
                  && (! svn_checksum_match(rep->sha1_checksum,
                                           args->rb->sha1_checksum)))
                return svn_error_createf(SVN_ERR_FS_CORRUPT,
                        svn_checksum_mismatch_err(rep->sha1_checksum,
                            args->rb->sha1_checksum, trail->pool,
                            _("SHA1 checksum mismatch on representation '%s'"),
                            args->rb->rep_key),
                        NULL);
            }
        }
    }
  else if (args->rb->offset > 0)
    {
      return
        svn_error_create
        (SVN_ERR_FS_REP_CHANGED, NULL,
         _("Null rep, but offset past zero already"));
    }
  else
    *(args->len) = 0;

  return SVN_NO_ERROR;
}
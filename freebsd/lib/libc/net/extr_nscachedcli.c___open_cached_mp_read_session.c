#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct cached_connection_params {int dummy; } ;
struct cached_connection_ {int mp_flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  CET_MP_READ_SESSION_REQUEST ; 
 int /*<<< orphan*/  __close_cached_connection (struct cached_connection_*) ; 
 struct cached_connection_* __open_cached_connection (struct cached_connection_params const*) ; 
 int safe_read (struct cached_connection_*,int*,int) ; 
 int safe_write (struct cached_connection_*,...) ; 
 int send_credentials (struct cached_connection_*,int /*<<< orphan*/ ) ; 
 size_t strlen (char const*) ; 

struct cached_connection_ *
__open_cached_mp_read_session(struct cached_connection_params const *params,
	const char *entry_name)
{
	struct cached_connection_ *connection, *retval;
	size_t name_size;
	int error_code;
	int result;

	retval = NULL;
	connection = __open_cached_connection(params);
	if (connection == NULL)
		return (NULL);
	connection->mp_flag = 1;

	result = send_credentials(connection, CET_MP_READ_SESSION_REQUEST);
	if (result != 0)
		goto fin;

	name_size = strlen(entry_name);
	result = safe_write(connection, &name_size, sizeof(size_t));
	if (result != 0)
		goto fin;

	result = safe_write(connection, entry_name, name_size);
	if (result != 0)
		goto fin;

	result = safe_read(connection, &error_code, sizeof(int));
	if (result != 0)
		goto fin;

	if (error_code != 0)
		result = error_code;

fin:
	if (result != 0)
		__close_cached_connection(connection);
	else
		retval = connection;
	return (retval);
}
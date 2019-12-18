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
struct nscd_connection_ {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CET_TRANSFORM_REQUEST ; 
 int /*<<< orphan*/  TRACE_IN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE_OUT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nscd_transform ; 
 int safe_read (struct nscd_connection_*,int*,int) ; 
 int safe_write (struct nscd_connection_*,...) ; 
 int send_credentials (struct nscd_connection_*,int /*<<< orphan*/ ) ; 
 size_t strlen (char const*) ; 

int
nscd_transform__(struct nscd_connection_ *connection,
	const char *entry_name, int transformation_type)
{
	size_t name_size;
	int error_code;
	int result;

	TRACE_IN(nscd_transform);

	error_code = -1;
	result = 0;
	result = send_credentials(connection, CET_TRANSFORM_REQUEST);
	if (result != 0)
		goto fin;

	if (entry_name != NULL)
		name_size = strlen(entry_name);
	else
		name_size = 0;

	result = safe_write(connection, &name_size, sizeof(size_t));
	if (result != 0)
		goto fin;

	result = safe_write(connection, &transformation_type, sizeof(int));
	if (result != 0)
		goto fin;

	if (entry_name != NULL) {
		result = safe_write(connection, entry_name, name_size);
		if (result != 0)
			goto fin;
	}

	result = safe_read(connection, &error_code, sizeof(int));
	if (result != 0)
		error_code = -1;

fin:
	TRACE_OUT(nscd_transform);
	return (error_code);
}
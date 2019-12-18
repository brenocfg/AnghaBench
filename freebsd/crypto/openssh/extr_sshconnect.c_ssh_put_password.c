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

/* Variables and functions */
 int ROUNDUP (scalar_t__,int) ; 
 int SSH_BUG_PASSWORDPAD ; 
 int datafellows ; 
 int /*<<< orphan*/  explicit_bzero (char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  packet_put_cstring (char*) ; 
 int /*<<< orphan*/  packet_put_string (char*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 scalar_t__ strlen (char*) ; 
 char* xcalloc (int,int) ; 

void
ssh_put_password(char *password)
{
	int size;
	char *padded;

	if (datafellows & SSH_BUG_PASSWORDPAD) {
		packet_put_cstring(password);
		return;
	}
	size = ROUNDUP(strlen(password) + 1, 32);
	padded = xcalloc(1, size);
	strlcpy(padded, password, size);
	packet_put_string(padded, size);
	explicit_bzero(padded, size);
	free(padded);
}
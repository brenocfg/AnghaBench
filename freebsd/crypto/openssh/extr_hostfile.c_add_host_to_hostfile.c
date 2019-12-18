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
struct sshkey {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int write_host_entry (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,struct sshkey const*,int) ; 

int
add_host_to_hostfile(const char *filename, const char *host,
    const struct sshkey *key, int store_hash)
{
	FILE *f;
	int success;

	if (key == NULL)
		return 1;	/* XXX ? */
	f = fopen(filename, "a");
	if (!f)
		return 0;
	success = write_host_entry(f, host, NULL, key, store_hash);
	fclose(f);
	return success;
}
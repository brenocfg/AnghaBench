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
typedef  size_t u_int ;
struct hostkeys {size_t num_entries; struct hostkeys* entries; int /*<<< orphan*/  key; struct hostkeys* file; struct hostkeys* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  explicit_bzero (struct hostkeys*,int) ; 
 int /*<<< orphan*/  free (struct hostkeys*) ; 
 int /*<<< orphan*/  sshkey_free (int /*<<< orphan*/ ) ; 

void
free_hostkeys(struct hostkeys *hostkeys)
{
	u_int i;

	for (i = 0; i < hostkeys->num_entries; i++) {
		free(hostkeys->entries[i].host);
		free(hostkeys->entries[i].file);
		sshkey_free(hostkeys->entries[i].key);
		explicit_bzero(hostkeys->entries + i, sizeof(*hostkeys->entries));
	}
	free(hostkeys->entries);
	explicit_bzero(hostkeys, sizeof(*hostkeys));
	free(hostkeys);
}
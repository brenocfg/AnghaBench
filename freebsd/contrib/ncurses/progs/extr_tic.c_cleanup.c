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
 int /*<<< orphan*/  fclose (scalar_t__) ; 
 int /*<<< orphan*/  free_namelist (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  namelst ; 
 int /*<<< orphan*/  perror (scalar_t__) ; 
 int remove (scalar_t__) ; 
 scalar_t__ tmp_fp ; 
 scalar_t__ to_remove ; 
 int unlink (scalar_t__) ; 

__attribute__((used)) static void
cleanup(void)
{
    int rc;

#if NO_LEAKS
    free_namelist(namelst);
#endif
    if (tmp_fp != 0)
	fclose(tmp_fp);
    if (to_remove != 0) {
#if HAVE_REMOVE
	rc = remove(to_remove);
#else
	rc = unlink(to_remove);
#endif
	if (rc != 0)
	    perror(to_remove);
    }
}
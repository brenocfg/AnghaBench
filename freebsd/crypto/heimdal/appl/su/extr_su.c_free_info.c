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
struct passwd {struct passwd* pw_shell; struct passwd* pw_dir; struct passwd* pw_passwd; struct passwd* pw_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct passwd*) ; 

__attribute__((used)) static void
free_info(struct passwd *p)
{
    free (p->pw_name);
    free (p->pw_passwd);
    free (p->pw_dir);
    free (p->pw_shell);
    free (p);
}
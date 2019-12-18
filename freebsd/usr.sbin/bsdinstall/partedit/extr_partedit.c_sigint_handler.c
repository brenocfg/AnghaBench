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
struct gmesh {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  end_dialog () ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  geom_deletetree (struct gmesh*) ; 
 int /*<<< orphan*/  geom_gettree (struct gmesh*) ; 
 int /*<<< orphan*/  gpart_revert_all (struct gmesh*) ; 

__attribute__((used)) static void
sigint_handler(int sig)
{
	struct gmesh mesh;

	/* Revert all changes and exit dialog-mode cleanly on SIGINT */
	geom_gettree(&mesh);
	gpart_revert_all(&mesh);
	geom_deletetree(&mesh);

	end_dialog();

	exit(1);
}
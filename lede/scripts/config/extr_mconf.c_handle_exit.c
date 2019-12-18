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
 int KEY_ESC ; 
 char* _ (char*) ; 
 scalar_t__ conf_get_changed () ; 
 int /*<<< orphan*/  conf_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dialog_clear () ; 
 int dialog_yesno (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  end_dialog (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filename ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  reset_subtitle () ; 
 int save_and_exit ; 
 int /*<<< orphan*/  saved_x ; 
 int /*<<< orphan*/  saved_y ; 
 int /*<<< orphan*/  silent ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int handle_exit(void)
{
	int res;

	save_and_exit = 1;
	reset_subtitle();
	dialog_clear();
	if (conf_get_changed())
		res = dialog_yesno(NULL,
				   _("Do you wish to save your new configuration?\n"
				     "(Press <ESC><ESC> to continue kernel configuration.)"),
				   6, 60);
	else
		res = -1;

	end_dialog(saved_x, saved_y);

	switch (res) {
	case 0:
		if (conf_write(filename)) {
			fprintf(stderr, _("\n\n"
					  "Error while writing of the configuration.\n"
					  "Your configuration changes were NOT saved."
					  "\n\n"));
			return 1;
		}
		/* fall through */
	case -1:
		if (!silent)
			printf(_("\n\n"
				 "*** End of the configuration.\n"
				 "*** Execute 'make' to start the build or try 'make help'."
				 "\n\n"));
		res = 0;
		break;
	default:
		if (!silent)
			fprintf(stderr, _("\n\n"
					  "Your configuration changes were NOT saved."
					  "\n\n"));
		if (res != KEY_ESC)
			res = 0;
	}

	return res;
}
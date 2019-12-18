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
 int /*<<< orphan*/  _IONBF ; 
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_strdup (char*) ; 
 char* g_strjoinv (char*,char**) ; 
 int /*<<< orphan*/  gtk_init (int*,char***) ; 
 int passphrase_dialog (char*) ; 
 int /*<<< orphan*/  setvbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 

int
main(int argc, char **argv)
{
	char *message;
	int result;

	gtk_init(&argc, &argv);

	if (argc > 1) {
		message = g_strjoinv(" ", argv + 1);
	} else {
		message = g_strdup("Enter your OpenSSH passphrase:");
	}

	setvbuf(stdout, 0, _IONBF, 0);
	result = passphrase_dialog(message);
	g_free(message);

	return (result);
}
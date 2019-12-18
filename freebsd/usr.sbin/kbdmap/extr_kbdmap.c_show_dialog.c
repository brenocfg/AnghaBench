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
struct keymap {char* desc; } ;
typedef  int /*<<< orphan*/  choice ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  asprintf (char**,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  do_kbdcontrol (struct keymap*) ; 
 int /*<<< orphan*/  do_vidfont (struct keymap*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 char* font ; 
 char* font_current ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (scalar_t__) ; 
 int /*<<< orphan*/  menu ; 
 int mkstemp (char*) ; 
 char* program ; 
 int /*<<< orphan*/  remove (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  system (char*) ; 
 int /*<<< orphan*/  vidcontrol (char*) ; 

__attribute__((used)) static void
show_dialog(struct keymap **km_sorted, int num_keymaps)
{
	FILE *fp;
	char *cmd, *dialog;
	char tmp_name[] = "/tmp/_kbd_lang.XXXX";
	int fd, i, size;

	fd = mkstemp(tmp_name);
	if (fd == -1) {
		fprintf(stderr, "Could not open temporary file \"%s\"\n",
		    tmp_name);
		exit(1);
	}
	asprintf(&dialog, "/usr/bin/dialog --clear --title \"Keyboard Menu\" "
			  "--menu \"%s\" 0 0 0", menu);

	/* start right font, assume that current font is equal
	 * to default font in /etc/rc.conf
	 *	
	 * $font is the font which require the language $lang; e.g.
	 * russian *need* a koi8 font
	 * $font_current is the current font from /etc/rc.conf
	 */
	if (font && strcmp(font, font_current))
		vidcontrol(font);

	/* Build up the command */
	size = 0;
	for (i=0; i<num_keymaps; i++) {
		/*
		 * Each 'font' is passed as ' "font" ""', so allow the
		 * extra space
		 */
		size += strlen(km_sorted[i]->desc) + 6;
	}

	/* Allow the space for '2> tmpfilename' redirection */
	size += strlen(tmp_name) + 3;

	cmd = (char *) malloc(strlen(dialog) + size + 1);
	strcpy(cmd, dialog);

	for (i=0; i<num_keymaps; i++) {
		strcat(cmd, " \"");
		strcat(cmd, km_sorted[i]->desc);
		strcat(cmd, "\"");
		strcat(cmd, " \"\"");
	}

	strcat(cmd, " 2>");
	strcat(cmd, tmp_name);

	/* Show the dialog.. */
	system(cmd);

	fp = fopen(tmp_name, "r");
	if (fp) {
		char choice[64];
		if (fgets(choice, sizeof(choice), fp) != NULL) {
			/* Find key for desc */
			for (i=0; i<num_keymaps; i++) {
				if (!strcmp(choice, km_sorted[i]->desc)) {
					if (!strcmp(program, "kbdmap"))
						do_kbdcontrol(km_sorted[i]);
					else
						do_vidfont(km_sorted[i]);
					break;
				}
			}
		} else {
			if (font != NULL && strcmp(font, font_current))
				/* Cancelled, restore old font */
				vidcontrol(font_current);
		}
		fclose(fp);
	} else
		fprintf(stderr, "Failed to open temporary file");

	/* Tidy up */
	remove(tmp_name);
	free(cmd);
	free(dialog);
	close(fd);
}
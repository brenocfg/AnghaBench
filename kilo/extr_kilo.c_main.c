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
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  editorOpen (char*) ; 
 int /*<<< orphan*/  editorProcessKeypress (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  editorRefreshScreen () ; 
 int /*<<< orphan*/  editorSelectSyntaxHighlight (char*) ; 
 int /*<<< orphan*/  editorSetStatusMessage (char*) ; 
 int /*<<< orphan*/  enableRawMode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  initEditor () ; 
 int /*<<< orphan*/  stderr ; 

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr,"Usage: kilo <filename>\n");
        exit(1);
    }

    initEditor();
    editorSelectSyntaxHighlight(argv[1]);
    editorOpen(argv[1]);
    enableRawMode(STDIN_FILENO);
    editorSetStatusMessage(
        "HELP: Ctrl-S = save | Ctrl-Q = quit | Ctrl-F = find");
    while(1) {
        editorRefreshScreen();
        editorProcessKeypress(STDIN_FILENO);
    }
    return 0;
}
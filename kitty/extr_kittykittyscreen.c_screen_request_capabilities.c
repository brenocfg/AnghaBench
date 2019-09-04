#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  buf ;
struct TYPE_6__ {int /*<<< orphan*/  blink; int /*<<< orphan*/  shape; } ;
struct TYPE_5__ {int /*<<< orphan*/  margin_bottom; int /*<<< orphan*/  margin_top; TYPE_4__* cursor; } ;
typedef  TYPE_1__ Screen ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/  CALLBACK (char*,char*,int /*<<< orphan*/ *) ; 
#define  CURSOR_BEAM 132 
#define  CURSOR_BLOCK 131 
#define  CURSOR_UNDERLINE 130 
 int /*<<< orphan*/  DCS ; 
#define  NO_CURSOR_SHAPE 129 
#define  NUM_OF_CURSOR_SHAPES 128 
 char* PyUnicode_AsUTF8 (int /*<<< orphan*/ *) ; 
 char* cursor_as_sgr (TYPE_4__*) ; 
 int snprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/  strcmp (char*,char const*) ; 
 int /*<<< orphan*/  write_escape_code_to_child (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 

void
screen_request_capabilities(Screen *self, char c, PyObject *q) {
    static char buf[128];
    int shape = 0;
    const char *query;
    switch(c) {
        case '+':
            CALLBACK("request_capabilities", "O", q);
            break;
        case '$':
            // report status
            query = PyUnicode_AsUTF8(q);
            if (strcmp(" q", query) == 0) {
                // cursor shape
                switch(self->cursor->shape) {
                    case NO_CURSOR_SHAPE:
                    case NUM_OF_CURSOR_SHAPES:
                        shape = 1; break;
                    case CURSOR_BLOCK:
                        shape = self->cursor->blink ? 0 : 2; break;
                    case CURSOR_UNDERLINE:
                        shape = self->cursor->blink ? 3 : 4; break;
                    case CURSOR_BEAM:
                        shape = self->cursor->blink ? 5 : 6; break;
                }
                shape = snprintf(buf, sizeof(buf), "1$r%d q", shape);
            } else if (strcmp("m", query) == 0) {
                // SGR
                shape = snprintf(buf, sizeof(buf), "1$r%sm", cursor_as_sgr(self->cursor));
            } else if (strcmp("r", query) == 0) {
                shape = snprintf(buf, sizeof(buf), "1$r%u;%ur", self->margin_top + 1, self->margin_bottom + 1);
            } else {
                shape = snprintf(buf, sizeof(buf), "0$r%s", query);
            }
            if (shape > 0) write_escape_code_to_child(self, DCS, buf);
            break;
    }
}
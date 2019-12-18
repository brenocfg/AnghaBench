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
struct cshape {int* shape; } ;

/* Variables and functions */
 int CONS_BLINK_CURSOR ; 
 int CONS_CHARCURSOR_COLORS ; 
 int CONS_CHAR_CURSOR ; 
 int CONS_DEFAULT_CURSOR ; 
 int CONS_HIDDEN_CURSOR ; 
 int CONS_LOCAL_CURSOR ; 
 int CONS_MOUSECURSOR_COLORS ; 
 int CONS_RESET_CURSOR ; 
 int CONS_SHAPEONLY_CURSOR ; 
 int /*<<< orphan*/  errx (int,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  printf (char*,int,int,int) ; 
 int /*<<< orphan*/  revert () ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strdup (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 char* strsep (char**,char*) ; 
 void* strtol (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
parse_cursor_params(char *param, struct cshape *shape)
{
	char *dupparam, *word;
	int type;

	param = dupparam = strdup(param);
	type = shape->shape[0];
	while ((word = strsep(&param, ",")) != NULL) {
		if (strcmp(word, "normal") == 0)
			type = 0;
		else if (strcmp(word, "destructive") == 0)
			type = CONS_BLINK_CURSOR | CONS_CHAR_CURSOR;
		else if (strcmp(word, "blink") == 0)
			type |= CONS_BLINK_CURSOR;
		else if (strcmp(word, "noblink") == 0)
			type &= ~CONS_BLINK_CURSOR;
		else if (strcmp(word, "block") == 0)
			type &= ~CONS_CHAR_CURSOR;
		else if (strcmp(word, "noblock") == 0)
			type |= CONS_CHAR_CURSOR;
		else if (strcmp(word, "hidden") == 0)
			type |= CONS_HIDDEN_CURSOR;
		else if (strcmp(word, "nohidden") == 0)
			type &= ~CONS_HIDDEN_CURSOR;
		else if (strncmp(word, "base=", 5) == 0)
			shape->shape[1] = strtol(word + 5, NULL, 0);
		else if (strncmp(word, "height=", 7) == 0)
			shape->shape[2] = strtol(word + 7, NULL, 0);
		else if (strcmp(word, "charcolors") == 0)
			type |= CONS_CHARCURSOR_COLORS;
		else if (strcmp(word, "mousecolors") == 0)
			type |= CONS_MOUSECURSOR_COLORS;
		else if (strcmp(word, "default") == 0)
			type |= CONS_DEFAULT_CURSOR;
		else if (strcmp(word, "shapeonly") == 0)
			type |= CONS_SHAPEONLY_CURSOR;
		else if (strcmp(word, "local") == 0)
			type |= CONS_LOCAL_CURSOR;
		else if (strcmp(word, "reset") == 0)
			type |= CONS_RESET_CURSOR;
		else if (strcmp(word, "show") == 0)
			printf("flags %#x, base %d, height %d\n",
			    type, shape->shape[1], shape->shape[2]);
		else {
			revert();
			errx(1,
			    "invalid parameters for -c starting at '%s%s%s'",
			    word, param != NULL ? "," : "",
			    param != NULL ? param : "");
		}
	}
	free(dupparam);
	shape->shape[0] = type;
}
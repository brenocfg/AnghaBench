#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char** Strings; int /*<<< orphan*/  term_names; } ;
struct TYPE_4__ {TYPE_3__ tterm; scalar_t__ startline; } ;
typedef  TYPE_1__ ENTRY ;

/* Variables and functions */
 char L_BRACE ; 
 int MAX_ENTRY_SIZE ; 
 char R_BRACE ; 
 unsigned int STRCOUNT ; 
 void* S_QUOTE ; 
 scalar_t__ VALID_STRING (char*) ; 
 int /*<<< orphan*/  _nc_STRCPY (char*,char*,scalar_t__) ; 
 int _nc_curr_line ; 
 int /*<<< orphan*/  _nc_first_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _nc_set_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _nc_write_entry (TYPE_3__*) ; 
 scalar_t__ isprint (int) ; 
 scalar_t__ strchr (char*,char) ; 
 scalar_t__ strlen (char*) ; 
 long strtol (char*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
write_it(ENTRY * ep)
{
    unsigned n;
    int ch;
    char *s, *d, *t;
    char result[MAX_ENTRY_SIZE];

    /*
     * Look for strings that contain %{number}, convert them to %'char',
     * which is shorter and runs a little faster.
     */
    for (n = 0; n < STRCOUNT; n++) {
	s = ep->tterm.Strings[n];
	if (VALID_STRING(s)
	    && strchr(s, L_BRACE) != 0) {
	    d = result;
	    t = s;
	    while ((ch = *t++) != 0) {
		*d++ = (char) ch;
		if (ch == '\\') {
		    *d++ = *t++;
		} else if ((ch == '%')
			   && (*t == L_BRACE)) {
		    char *v = 0;
		    long value = strtol(t + 1, &v, 0);
		    if (v != 0
			&& *v == R_BRACE
			&& value > 0
			&& value != '\\'	/* FIXME */
			&& value < 127
			&& isprint((int) value)) {
			*d++ = S_QUOTE;
			*d++ = (char) value;
			*d++ = S_QUOTE;
			t = (v + 1);
		    }
		}
	    }
	    *d = 0;
	    if (strlen(result) < strlen(s))
		_nc_STRCPY(s, result, strlen(s) + 1);
	}
    }

    _nc_set_type(_nc_first_name(ep->tterm.term_names));
    _nc_curr_line = (int) ep->startline;
    _nc_write_entry(&ep->tterm);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {size_t used; char* text; } ;

/* Variables and functions */
 scalar_t__ F_TCONVERR ; 
 scalar_t__ F_TERMCAP ; 
 int /*<<< orphan*/  UChar (char) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ isspace (int /*<<< orphan*/ ) ; 
 TYPE_1__ outbuf ; 
 scalar_t__ outform ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  stdout ; 

int
show_entry(void)
{
    /*
     * Trim any remaining whitespace.
     */
    if (outbuf.used != 0) {
	bool infodump = (outform != F_TERMCAP && outform != F_TCONVERR);
	char delim = (char) (infodump ? ',' : ':');
	int j;

	for (j = (int) outbuf.used - 1; j > 0; --j) {
	    char ch = outbuf.text[j];
	    if (ch == '\n') {
		;
	    } else if (isspace(UChar(ch))) {
		outbuf.used = (size_t) j;
	    } else if (!infodump && ch == '\\') {
		outbuf.used = (size_t) j;
	    } else if (ch == delim && (j == 0 || outbuf.text[j - 1] != '\\')) {
		outbuf.used = (size_t) (j + 1);
	    } else {
		break;
	    }
	}
	outbuf.text[outbuf.used] = '\0';
    }
    (void) fputs(outbuf.text, stdout);
    putchar('\n');
    return (int) outbuf.used;
}
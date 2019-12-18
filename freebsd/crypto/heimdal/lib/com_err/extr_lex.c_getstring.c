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
typedef  int /*<<< orphan*/  x ;
struct TYPE_2__ {int /*<<< orphan*/ * string; } ;

/* Variables and functions */
 int EOF ; 
 int STRING ; 
 int /*<<< orphan*/  _lex_error_message (char*) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int input () ; 
 int /*<<< orphan*/  lineno ; 
 int /*<<< orphan*/ * strdup (char*) ; 
 TYPE_1__ yylval ; 

__attribute__((used)) static int
getstring(void)
{
    char x[128];
    int i = 0;
    int c;
    int quote = 0;
    while(i < sizeof(x) - 1 && (c = input()) != EOF){
	if(quote) {
	    x[i++] = c;
	    quote = 0;
	    continue;
	}
	if(c == '\n'){
	    _lex_error_message("unterminated string");
	    lineno++;
	    break;
	}
	if(c == '\\'){
	    quote++;
	    continue;
	}
	if(c == '\"')
	    break;
	x[i++] = c;
    }
    x[i] = '\0';
    yylval.string = strdup(x);
    if (yylval.string == NULL)
        err(1, "malloc");
    return STRING;
}
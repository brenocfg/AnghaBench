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
 int EOF ; 
 int /*<<< orphan*/  error_message (char*) ; 
 int input () ; 
 int /*<<< orphan*/  lineno ; 
 char* strdup (char*) ; 

__attribute__((used)) static char *
handle_string(void)
{
    char x[1024];
    int i = 0;
    int c;
    int quote = 0;
    while((c = input()) != EOF){
	if(quote) {
	    x[i++] = '\\';
	    x[i++] = c;
	    quote = 0;
	    continue;
	}
	if(c == '\n'){
	    error_message("unterminated string");
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
    return strdup(x);
}
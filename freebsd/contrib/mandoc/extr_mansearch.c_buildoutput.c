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
struct dbm_page {char* name; char* sect; char* arch; int /*<<< orphan*/  addr; int /*<<< orphan*/  desc; } ;

/* Variables and functions */
#define  KEY_Nd 131 
#define  KEY_Nm 130 
#define  KEY_arch 129 
#define  KEY_sec 128 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dbm_macro_bypage (size_t,int /*<<< orphan*/ ) ; 
 char* dbm_macro_next () ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  lstcat (char*,size_t*,char const*,char*) ; 
 int lstlen (char const*,int) ; 
 int /*<<< orphan*/  mandoc_asprintf (char**,char*,char const*,char const*,char*) ; 
 char* mandoc_malloc (size_t) ; 
 char* mandoc_strdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
buildoutput(size_t im, struct dbm_page *page)
{
	const char	*oldoutput, *sep, *input;
	char		*output, *newoutput, *value;
	size_t		 sz, i;

	switch (im) {
	case KEY_Nd:
		return mandoc_strdup(page->desc);
	case KEY_Nm:
		input = page->name;
		break;
	case KEY_sec:
		input = page->sect;
		break;
	case KEY_arch:
		input = page->arch;
		if (input == NULL)
			input = "all\0";
		break;
	default:
		input = NULL;
		break;
	}

	if (input != NULL) {
		sz = lstlen(input, 3) + 1;
		output = mandoc_malloc(sz);
		i = 0;
		lstcat(output, &i, input, " # ");
		output[i++] = '\0';
		assert(i == sz);
		return output;
	}

	output = NULL;
	dbm_macro_bypage(im - 2, page->addr);
	while ((value = dbm_macro_next()) != NULL) {
		if (output == NULL) {
			oldoutput = "";
			sep = "";
		} else {
			oldoutput = output;
			sep = " # ";
		}
		mandoc_asprintf(&newoutput, "%s%s%s", oldoutput, sep, value);
		free(output);
		output = newoutput;
	}
	return output;
}
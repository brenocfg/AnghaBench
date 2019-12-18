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
 int /*<<< orphan*/  INSERT_COLON ; 
 int /*<<< orphan*/  INSERT_NEWLINE ; 
 int /*<<< orphan*/  INSERT_SPACE ; 
 char const* MM_NULLACT ; 
 char const* MM_NULLLBL ; 
 char const* MM_NULLTAG ; 
 char const* MM_NULLTXT ; 
 char* malloc (size_t) ; 
 char* nextcomp (char*) ; 
 char const* sevinfo (int) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlcat (char*,char const*,size_t) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static char *
printfmt(char *msgverb, long class, const char *label, int sev,
    const char *text, const char *act, const char *tag)
{
	size_t size;
	char *comp, *output;
	const char *sevname;

	size = 32;
	if (label != MM_NULLLBL)
		size += strlen(label);
	if ((sevname = sevinfo(sev)) != NULL)
		size += strlen(sevname);
	if (text != MM_NULLTXT)
		size += strlen(text);
	if (act != MM_NULLACT)
		size += strlen(act);
	if (tag != MM_NULLTAG)
		size += strlen(tag);

	if ((output = malloc(size)) == NULL)
		return (NULL);
	*output = '\0';
	while ((comp = nextcomp(msgverb)) != NULL) {
		if (strcmp(comp, "label") == 0 && label != MM_NULLLBL) {
			INSERT_COLON;
			strlcat(output, label, size);
		} else if (strcmp(comp, "severity") == 0 && sevname != NULL) {
			INSERT_COLON;
			strlcat(output, sevinfo(sev), size);
		} else if (strcmp(comp, "text") == 0 && text != MM_NULLTXT) {
			INSERT_COLON;
			strlcat(output, text, size);
		} else if (strcmp(comp, "action") == 0 && act != MM_NULLACT) {
			INSERT_NEWLINE;
			strlcat(output, "TO FIX: ", size);
			strlcat(output, act, size);
		} else if (strcmp(comp, "tag") == 0 && tag != MM_NULLTAG) {
			INSERT_SPACE;
			strlcat(output, tag, size);
		}
	}
	INSERT_NEWLINE;
	return (output);
}
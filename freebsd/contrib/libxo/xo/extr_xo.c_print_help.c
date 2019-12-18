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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
print_help (void)
{
    fprintf(stderr,
"Usage: xo [options] format [fields]\n"
"    --close <path>        Close tags for the given path\n"
"    --close-instance <name> Close an open instance name\n"
"    --close-list <name>   Close an open list name\n"
"    --continuation OR -C  Output belongs on same line as previous output\n"
"    --depth <num>         Set the depth for pretty printing\n"
"    --help                Display this help text\n"
"    --html OR -H          Generate HTML output\n"
"    --instance OR -I <name> Wrap in an instance of the given name\n"
"    --json OR -J          Generate JSON output\n"
"    --leading-xpath <path> OR -l <path> "
	    "Add a prefix to generated XPaths (HTML)\n"
"    --not-first           Indicate this object is not the first (JSON)\n"
"    --open <path>         Open tags for the given path\n"
"    --open-instance <name> Open an instance given by name\n"
"    --open-list <name>   Open a list given by name\n"
"    --option <opts> -or -O <opts>  Give formatting options\n"
"    --pretty OR -p        Make 'pretty' output (add indent, newlines)\n"
"    --style <style> OR -s <style>  "
	    "Generate given style (xml, json, text, html)\n"
"    --text OR -T          Generate text output (the default style)\n"
"    --top-wrap            Generate a top-level object wrapper (JSON)\n"
"    --version             Display version information\n"
"    --warn OR -W          Display warnings in text on stderr\n"
"    --warn-xml            Display warnings in xml on stdout\n"
"    --wrap <path>         Wrap output in a set of containers\n"
"    --xml OR -X           Generate XML output\n"
"    --xpath               Add XPath data to HTML output\n");
}
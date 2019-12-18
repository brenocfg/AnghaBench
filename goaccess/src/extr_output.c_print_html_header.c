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
struct TYPE_2__ {char* html_custom_css; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  DOC_LANG ; 
 char* _ (int /*<<< orphan*/ ) ; 
 char* app_css ; 
 char* bootstrap_css ; 
 TYPE_1__ conf ; 
 char* fa_css ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  print_html_title (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
print_html_header (FILE * fp)
{
  fprintf (fp,
  "<!DOCTYPE html>"
  "<html lang='%s'>"
  "<head>"
  "<meta charset='UTF-8'>"
  "<meta name='referrer' content='no-referrer'>"
  "<meta http-equiv='X-UA-Compatible' content='IE=edge'>"
  "<meta name='google' content='notranslate'>"
  "<meta name='viewport' content='width=device-width, initial-scale=1'>"
  "<meta name='robots' content='noindex, nofollow'>", _(DOC_LANG));

  /* Output base64 encoded goaccess favicon.ico*/
  fprintf (fp, "<link rel='icon' href='data:image/x-icon;base64,AAABAAEA"
  "EBAQAAEABAAoAQAAFgAAACgAAAAQAAAAIAAAAAEABAAAAAAAgAAAAAAAAAAAAAAAEAAAA"
  "AAAAADGxsYAWFhYABwcHABfAP8A/9dfAADXrwAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
  "AAAAAAAAAAAAAAAAAAAAAAIiIiIiIiIiIjMlUkQgAiIiIiIiIiIiIiIzJVJEIAAAIiIiI"
  "iIiIiIiMyVSRCAAIiIiIiIiIiIiIRERERERERERERERERERERIiIiIiIiIiIgACVVUiIi"
  "IiIiIiIiIiIiIAAlVVIiIiIiIiIiIiIiIhEREREREREREREREREREREAAAAAAAAAAAAAA"
  "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
  "AA' type='image/x-icon' />");

  print_html_title (fp);

  fprintf (fp, "<style>%s</style>", fa_css);
  fprintf (fp, "<style>%s</style>", bootstrap_css);
  fprintf (fp, "<style>%s</style>", app_css);
  /* load custom CSS file, if any */
  if (conf.html_custom_css)
    fprintf (fp, "<link rel='stylesheet' href='%s'>", conf.html_custom_css);

  fprintf (fp,
  "</head>"
  "<body>");
}
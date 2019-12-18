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
struct TYPE_2__ {char* html_custom_js; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* app_js ; 
 char* charts_js ; 
 TYPE_1__ conf ; 
 char* d3_js ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 char* hogan_js ; 

__attribute__((used)) static void
print_html_footer (FILE * fp)
{
  fprintf (fp, "<script>%s</script>", d3_js);
  fprintf (fp, "<script>%s</script>", hogan_js);
  fprintf (fp, "<script>%s</script>", app_js);
  fprintf (fp, "<script>%s</script>", charts_js);

  /* load custom JS file, if any */
  if (conf.html_custom_js)
    fprintf (fp, "<script src='%s'></script>", conf.html_custom_js);

  fprintf (fp, "</body>");
  fprintf (fp, "</html>");
}
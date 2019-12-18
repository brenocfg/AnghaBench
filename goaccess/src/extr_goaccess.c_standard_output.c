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
struct TYPE_2__ {scalar_t__ output_format_idx; } ;

/* Variables and functions */
 TYPE_1__ conf ; 
 scalar_t__ find_output_type (char**,char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  glog ; 
 int /*<<< orphan*/  holder ; 
 int /*<<< orphan*/  output_csv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  output_json (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  process_html (char*) ; 

__attribute__((used)) static void
standard_output (void)
{
  char *csv = NULL, *json = NULL, *html = NULL;

  /* CSV */
  if (find_output_type (&csv, "csv", 1) == 0)
    output_csv (glog, holder, csv);
  /* JSON */
  if (find_output_type (&json, "json", 1) == 0)
    output_json (glog, holder, json);
  /* HTML */
  if (find_output_type (&html, "html", 1) == 0 || conf.output_format_idx == 0)
    process_html (html);

  free (csv);
  free (html);
  free (json);
}
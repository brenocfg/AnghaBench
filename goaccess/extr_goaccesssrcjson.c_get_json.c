#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ size; int /*<<< orphan*/  buf; } ;
typedef  int /*<<< orphan*/  GLog ;
typedef  TYPE_1__ GJSON ;
typedef  int /*<<< orphan*/  GHolder ;

/* Variables and functions */
 int escape_html_output ; 
 int /*<<< orphan*/  free_json (TYPE_1__*) ; 
 TYPE_1__* init_json_output (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* xstrdup (int /*<<< orphan*/ ) ; 

char *
get_json (GLog * glog, GHolder * holder, int escape_html)
{
  GJSON *json = NULL;
  char *buf = NULL;

  if (holder == NULL)
    return NULL;

  escape_html_output = escape_html;
  if ((json = init_json_output (glog, holder)) && json->size > 0) {
    buf = xstrdup (json->buf);
    free_json (json);
  }

  return buf;
}
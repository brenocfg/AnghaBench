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
struct TYPE_2__ {char* name; int /*<<< orphan*/  length; scalar_t__ source; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_JS_CODES ; 
 TYPE_1__* js_codes ; 
 int /*<<< orphan*/  js_entry () ; 
 int js_eval (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,char*) ; 
 int /*<<< orphan*/  show_free_mem (int) ; 

__attribute__((used)) static int jerry_task_init(void) {
  DECLARE_JS_CODES;

  js_entry();

  /* run rest of the js files first */
  show_free_mem(2);
  for (int src = 1; js_codes[src].source; src++) {
    int retcode = js_eval(js_codes[src].source, js_codes[src].length);
    if (retcode != 0) {
      printf("js_eval failed code(%d) [%s]\r\n", retcode, js_codes[src].name);
      return -1;
    }
  }

  /* run main.js */
  int retcode = js_eval(js_codes[0].source, js_codes[0].length);
  if (retcode != 0) {
    printf("js_eval failed code(%d) [%s]\r\n", retcode, js_codes[0].name);
    return -2;
  }
  show_free_mem(3);
  return 0;
}
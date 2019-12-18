#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int module; } ;
typedef  TYPE_1__ GColors ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int get_module_enum (char*) ; 
 char* strrchr (char*,char) ; 
 char* xstrdup (char const*) ; 

__attribute__((used)) static int
parse_module_color (GColors * color, const char *value)
{
  char *line = xstrdup (value), *p;

  p = strrchr (line, ' ');
  if (!p || !*(p + 1)) {
    LOG_DEBUG (("attempted to parse color module: %s\n", value));
    goto clean;
  }

  if ((color->module = get_module_enum (p + 1)) == -1)
    LOG_DEBUG (("attempted to parse color module: %s\n", value));

clean:
  free (line);

  return 0;
}
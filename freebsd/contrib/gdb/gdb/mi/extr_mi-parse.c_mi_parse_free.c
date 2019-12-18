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
struct mi_parse {int /*<<< orphan*/ * argv; struct mi_parse* args; struct mi_parse* token; struct mi_parse* command; } ;

/* Variables and functions */
 int /*<<< orphan*/  freeargv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfree (struct mi_parse*) ; 

void
mi_parse_free (struct mi_parse *parse)
{
  if (parse == NULL)
    return;
  if (parse->command != NULL)
    xfree (parse->command);
  if (parse->token != NULL)
    xfree (parse->token);
  if (parse->args != NULL)
    xfree (parse->args);
  if (parse->argv != NULL)
    freeargv (parse->argv);
  xfree (parse);
}
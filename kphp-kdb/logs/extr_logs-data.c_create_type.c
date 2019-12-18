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
struct lev_logs_create_type {int /*<<< orphan*/  text_len; int /*<<< orphan*/  text; } ;

/* Variables and functions */
 int /*<<< orphan*/  buff ; 
 char* create_type_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

char *create_type (struct lev_logs_create_type *E) {
  strcpy (buff, E->text);
  return create_type_buf (buff, E->text_len);
}
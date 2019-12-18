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
struct tl_type {int name; int constructors_num; int flags; int params_num; int /*<<< orphan*/  params_types; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int TLS_TYPE ; 
 int schema_version ; 
 int /*<<< orphan*/  wint (int) ; 
 int /*<<< orphan*/  wll (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wstr (int /*<<< orphan*/ ) ; 

void write_type (struct tl_type *t) {
  wint (schema_version >= 1 ? TLS_TYPE : 1);
  wint (t->name);
  wstr (t->id);
  wint (t->constructors_num);
  wint (t->flags);
  wint (t->params_num);
  wll (t->params_types);
}
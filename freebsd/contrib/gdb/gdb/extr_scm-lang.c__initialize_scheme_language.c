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
struct objfile {int dummy; } ;

/* Variables and functions */
 int TARGET_CHAR_BIT ; 
 int TARGET_LONG_BIT ; 
 int /*<<< orphan*/  TYPE_CODE_INT ; 
 int /*<<< orphan*/  add_language (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  builtin_type_scm ; 
 int /*<<< orphan*/  init_type (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,struct objfile*) ; 
 int /*<<< orphan*/  scm_language_defn ; 

void
_initialize_scheme_language (void)
{
  add_language (&scm_language_defn);
  builtin_type_scm = init_type (TYPE_CODE_INT,
				TARGET_LONG_BIT / TARGET_CHAR_BIT,
				0, "SCM", (struct objfile *) NULL);
}
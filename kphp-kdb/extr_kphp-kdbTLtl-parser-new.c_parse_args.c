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
struct tree {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PARSE_FAIL ; 
 int /*<<< orphan*/  PARSE_INIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PARSE_TRY_OPT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_args1 ; 
 int /*<<< orphan*/  parse_args2 ; 
 int /*<<< orphan*/  parse_args3 ; 
 int /*<<< orphan*/  parse_args4 ; 
 int /*<<< orphan*/  type_args ; 

struct tree *parse_args (void) {
  PARSE_INIT (type_args);
  PARSE_TRY_OPT (parse_args1);
  PARSE_TRY_OPT (parse_args2);
  PARSE_TRY_OPT (parse_args3);
  PARSE_TRY_OPT (parse_args4);
  PARSE_FAIL;
}
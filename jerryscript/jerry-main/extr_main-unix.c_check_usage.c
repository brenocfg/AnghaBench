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

/* Variables and functions */
 int /*<<< orphan*/  JERRY_LOG_LEVEL_ERROR ; 
 int /*<<< orphan*/  JERRY_STANDALONE_EXIT_CODE_FAIL ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_port_log (int /*<<< orphan*/ ,char*,char const*,char const*,char const*) ; 

__attribute__((used)) static void
check_usage (bool condition, /**< the condition that must hold */
             const char *name, /**< name of the application (argv[0]) */
             const char *msg, /**< error message to print if condition does not hold */
             const char *opt) /**< optional part of the error message */
{
  if (!condition)
  {
    jerry_port_log (JERRY_LOG_LEVEL_ERROR, "%s: %s%s\n", name, msg, opt != NULL ? opt : "");
    exit (JERRY_STANDALONE_EXIT_CODE_FAIL);
  }
}
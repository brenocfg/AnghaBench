#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * cmd_handler_t ;
typedef  scalar_t__ apr_size_t ;
struct TYPE_3__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct TYPE_4__ {int /*<<< orphan*/ * handler; TYPE_1__ cmd; } ;

/* Variables and functions */
 TYPE_2__* cmd_hash ; 
 scalar_t__ cmd_hash_func (char const*,scalar_t__) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char const*,scalar_t__) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static cmd_handler_t
cmd_lookup(const char *cmd)
{
  apr_size_t value;
  apr_size_t len = strlen(cmd);

  /* Malicious data that our hash function may not like? */
  if (len == 0)
    return NULL;

  /* Hash lookup. */
  value = cmd_hash_func(cmd, len);

  /* Hit? */
  if (cmd_hash[value].cmd.len != len)
    return NULL;

  if (memcmp(cmd_hash[value].cmd.data, cmd, len))
    return NULL;

  /* Yes! */
  return cmd_hash[value].handler;
}
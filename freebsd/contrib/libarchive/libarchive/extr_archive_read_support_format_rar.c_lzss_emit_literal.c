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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {int /*<<< orphan*/  position; } ;
struct rar {TYPE_1__ lzss; } ;

/* Variables and functions */
 int /*<<< orphan*/ * lzss_current_pointer (TYPE_1__*) ; 

__attribute__((used)) static inline void
lzss_emit_literal(struct rar *rar, uint8_t literal)
{
  *lzss_current_pointer(&rar->lzss) = literal;
  rar->lzss.position++;
}
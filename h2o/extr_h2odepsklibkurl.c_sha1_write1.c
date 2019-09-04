#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int /*<<< orphan*/  byteCount; } ;
typedef  TYPE_1__ sha1nfo ;

/* Variables and functions */
 int /*<<< orphan*/  sha1_add (TYPE_1__*,int /*<<< orphan*/ ) ; 

void sha1_write1(sha1nfo *s, uint8_t data)
{
	++s->byteCount;
	sha1_add(s, data);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {int /*<<< orphan*/ * b; } ;
struct TYPE_6__ {int bufOffset; TYPE_1__ buf; } ;
typedef  TYPE_2__ sha1nfo ;

/* Variables and functions */
 int BLOCK_LENGTH ; 
 int /*<<< orphan*/  sha1_hashBlock (TYPE_2__*) ; 

__attribute__((used)) static inline void sha1_add(sha1nfo *s, uint8_t data)
{
	s->buf.b[s->bufOffset ^ 3] = data;
	if (++s->bufOffset == BLOCK_LENGTH) {
		sha1_hashBlock(s);
		s->bufOffset = 0;
	}
}
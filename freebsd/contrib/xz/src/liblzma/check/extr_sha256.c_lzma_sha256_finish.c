#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int size; int /*<<< orphan*/ * state; } ;
struct TYPE_9__ {TYPE_2__ sha256; } ;
struct TYPE_7__ {int* u8; int /*<<< orphan*/ * u32; int /*<<< orphan*/ * u64; } ;
struct TYPE_10__ {TYPE_3__ state; TYPE_1__ buffer; } ;
typedef  TYPE_4__ lzma_check_state ;

/* Variables and functions */
 int /*<<< orphan*/  conv32be (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  conv64be (int) ; 
 int /*<<< orphan*/  process (TYPE_4__*) ; 

extern void
lzma_sha256_finish(lzma_check_state *check)
{
	// Add padding as described in RFC 3174 (it describes SHA-1 but
	// the same padding style is used for SHA-256 too).
	size_t pos = check->state.sha256.size & 0x3F;
	check->buffer.u8[pos++] = 0x80;

	while (pos != 64 - 8) {
		if (pos == 64) {
			process(check);
			pos = 0;
		}

		check->buffer.u8[pos++] = 0x00;
	}

	// Convert the message size from bytes to bits.
	check->state.sha256.size *= 8;

	check->buffer.u64[(64 - 8) / 8] = conv64be(check->state.sha256.size);

	process(check);

	for (size_t i = 0; i < 8; ++i)
		check->buffer.u32[i] = conv32be(check->state.sha256.state[i]);

	return;
}
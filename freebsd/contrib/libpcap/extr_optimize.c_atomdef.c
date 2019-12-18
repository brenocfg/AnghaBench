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
struct stmt {scalar_t__ code; int k; } ;

/* Variables and functions */
 int A_ATOM ; 
#define  BPF_ALU 133 
 int BPF_CLASS (scalar_t__) ; 
#define  BPF_LD 132 
#define  BPF_LDX 131 
#define  BPF_MISC 130 
 int /*<<< orphan*/  BPF_MISCOP (scalar_t__) ; 
#define  BPF_ST 129 
#define  BPF_STX 128 
 int /*<<< orphan*/  BPF_TAX ; 
 scalar_t__ NOP ; 
 int X_ATOM ; 

__attribute__((used)) static int
atomdef(struct stmt *s)
{
	if (s->code == NOP)
		return -1;

	switch (BPF_CLASS(s->code)) {

	case BPF_LD:
	case BPF_ALU:
		return A_ATOM;

	case BPF_LDX:
		return X_ATOM;

	case BPF_ST:
	case BPF_STX:
		return s->k;

	case BPF_MISC:
		return BPF_MISCOP(s->code) == BPF_TAX ? X_ATOM : A_ATOM;
	}
	return -1;
}
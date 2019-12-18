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
 int /*<<< orphan*/  AF_FLAG ; 
 int /*<<< orphan*/  AF_OPS ; 
 int /*<<< orphan*/  CPU ; 
 int /*<<< orphan*/  DF_FLAG ; 
 int /*<<< orphan*/  JIT_BLOCK ; 
 int /*<<< orphan*/  LOCAL ; 
 int /*<<< orphan*/  MACRO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEM_READ ; 
 int /*<<< orphan*/  MEM_WRITE ; 
 int /*<<< orphan*/  OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PF_FLAG ; 
 int /*<<< orphan*/  PF_RES ; 
 int /*<<< orphan*/  SF_FLAG ; 
 int /*<<< orphan*/  SF_RES ; 
 int /*<<< orphan*/  TLB ; 
 int /*<<< orphan*/  TLB_ENTRY ; 
 int /*<<< orphan*/  ZF_FLAG ; 
 int /*<<< orphan*/  ZF_RES ; 
 int /*<<< orphan*/  ax ; 
 int /*<<< orphan*/  bp ; 
 int /*<<< orphan*/  bx ; 
 int /*<<< orphan*/  cf ; 
 int /*<<< orphan*/  code ; 
 int /*<<< orphan*/  cpu_state ; 
 int /*<<< orphan*/  cx ; 
 int /*<<< orphan*/  data_minus_addr ; 
 int /*<<< orphan*/  df_offset ; 
 int /*<<< orphan*/  di ; 
 int /*<<< orphan*/  dirty_page ; 
 int /*<<< orphan*/  dx ; 
 int /*<<< orphan*/  eax ; 
 int /*<<< orphan*/  ebp ; 
 int /*<<< orphan*/  ebx ; 
 int /*<<< orphan*/  ecx ; 
 int /*<<< orphan*/  edi ; 
 int /*<<< orphan*/  edx ; 
 int /*<<< orphan*/  eflags ; 
 int /*<<< orphan*/  eip ; 
 int /*<<< orphan*/  entries ; 
 int /*<<< orphan*/  esi ; 
 int /*<<< orphan*/  esp ; 
 int /*<<< orphan*/  flags_res ; 
 int /*<<< orphan*/  fsw ; 
 int /*<<< orphan*/  gs ; 
 int /*<<< orphan*/  jit_block ; 
 int /*<<< orphan*/  jit_frame ; 
 int /*<<< orphan*/  last_block ; 
 int /*<<< orphan*/  of ; 
 int /*<<< orphan*/  op1 ; 
 int /*<<< orphan*/  op2 ; 
 int /*<<< orphan*/  page ; 
 int /*<<< orphan*/  page_if_writable ; 
 int /*<<< orphan*/  res ; 
 int /*<<< orphan*/  ret_cache ; 
 int /*<<< orphan*/  segfault_addr ; 
 int /*<<< orphan*/  segfault_type ; 
 int /*<<< orphan*/  si ; 
 int /*<<< orphan*/  sp ; 
 int /*<<< orphan*/  tlb ; 
 int /*<<< orphan*/  tlb_entry ; 
 int /*<<< orphan*/  tls_ptr ; 
 int /*<<< orphan*/  value ; 
 int /*<<< orphan*/  value_addr ; 
 int /*<<< orphan*/  xmm ; 

void cpu() {
    OFFSET(CPU, cpu_state, eax);
    OFFSET(CPU, cpu_state, ebx);
    OFFSET(CPU, cpu_state, ecx);
    OFFSET(CPU, cpu_state, edx);
    OFFSET(CPU, cpu_state, esi);
    OFFSET(CPU, cpu_state, edi);
    OFFSET(CPU, cpu_state, ebp);
    OFFSET(CPU, cpu_state, esp);
    OFFSET(CPU, cpu_state, ax);
    OFFSET(CPU, cpu_state, bx);
    OFFSET(CPU, cpu_state, cx);
    OFFSET(CPU, cpu_state, dx);
    OFFSET(CPU, cpu_state, si);
    OFFSET(CPU, cpu_state, di);
    OFFSET(CPU, cpu_state, bp);
    OFFSET(CPU, cpu_state, sp);
    OFFSET(CPU, cpu_state, eip);
    OFFSET(CPU, cpu_state, gs);
    OFFSET(CPU, cpu_state, tls_ptr);

    OFFSET(CPU, cpu_state, eflags);
    OFFSET(CPU, cpu_state, of);
    OFFSET(CPU, cpu_state, cf);
    OFFSET(CPU, cpu_state, res);
    OFFSET(CPU, cpu_state, op1);
    OFFSET(CPU, cpu_state, op2);
    OFFSET(CPU, cpu_state, flags_res);
    OFFSET(CPU, cpu_state, df_offset);
    OFFSET(CPU, cpu_state, fsw);
    OFFSET(CPU, cpu_state, xmm);
    MACRO(PF_RES);
    MACRO(ZF_RES);
    MACRO(SF_RES);
    MACRO(AF_OPS);
    MACRO(PF_FLAG);
    MACRO(AF_FLAG);
    MACRO(ZF_FLAG);
    MACRO(SF_FLAG);
    MACRO(DF_FLAG);

    OFFSET(LOCAL, jit_frame, bp);
    OFFSET(LOCAL, jit_frame, value);
    OFFSET(LOCAL, jit_frame, value_addr);
    OFFSET(LOCAL, jit_frame, last_block);
    OFFSET(LOCAL, jit_frame, ret_cache);
    OFFSET(CPU, cpu_state, segfault_addr);
    OFFSET(CPU, cpu_state, segfault_type);
    MACRO(MEM_READ);
    MACRO(MEM_WRITE);

    OFFSET(JIT_BLOCK, jit_block, code);

    OFFSET(TLB, tlb, entries);
    OFFSET(TLB, tlb, dirty_page);
    OFFSET(TLB_ENTRY, tlb_entry, page);
    OFFSET(TLB_ENTRY, tlb_entry, page_if_writable);
    OFFSET(TLB_ENTRY, tlb_entry, data_minus_addr);
}
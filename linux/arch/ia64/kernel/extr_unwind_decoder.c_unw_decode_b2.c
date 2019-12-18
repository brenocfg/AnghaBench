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
typedef  int /*<<< orphan*/  unw_word ;

/* Variables and functions */
 int /*<<< orphan*/  B2 ; 
 int /*<<< orphan*/  UNW_DEC_EPILOGUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char,void*) ; 
 int /*<<< orphan*/  unw_decode_uleb128 (unsigned char**) ; 

__attribute__((used)) static unsigned char *
unw_decode_b2 (unsigned char *dp, unsigned char code, void *arg)
{
  unw_word t;

  t = unw_decode_uleb128 (&dp);
  UNW_DEC_EPILOGUE(B2, t, (code & 0x1f), arg);
  return dp;
}
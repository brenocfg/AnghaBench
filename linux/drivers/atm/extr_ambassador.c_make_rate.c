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
typedef  unsigned char u16 ;
typedef  int rounding ;

/* Variables and functions */
 int DBG_FLOW ; 
 int DBG_QOS ; 
 int EINVAL ; 
 int /*<<< orphan*/  PRINTD (int,char*,unsigned int,...) ; 
#define  round_down 130 
#define  round_nearest 129 
#define  round_up 128 

__attribute__((used)) static int make_rate (unsigned int rate, rounding r,
		      u16 * bits, unsigned int * actual) {
  unsigned char exp = -1; // hush gcc
  unsigned int man = -1;  // hush gcc
  
  PRINTD (DBG_FLOW|DBG_QOS, "make_rate %u", rate);
  
  // rates in cells per second, ITU format (nasty 16-bit floating-point)
  // given 5-bit e and 9-bit m:
  // rate = EITHER (1+m/2^9)*2^e    OR 0
  // bits = EITHER 1<<14 | e<<9 | m OR 0
  // (bit 15 is "reserved", bit 14 "non-zero")
  // smallest rate is 0 (special representation)
  // largest rate is (1+511/512)*2^31 = 4290772992 (< 2^32-1)
  // smallest non-zero rate is (1+0/512)*2^0 = 1 (> 0)
  // simple algorithm:
  // find position of top bit, this gives e
  // remove top bit and shift (rounding if feeling clever) by 9-e
  
  // ucode bug: please don't set bit 14! so 0 rate not representable
  
  if (rate > 0xffc00000U) {
    // larger than largest representable rate
    
    if (r == round_up) {
	return -EINVAL;
    } else {
      exp = 31;
      man = 511;
    }
    
  } else if (rate) {
    // representable rate
    
    exp = 31;
    man = rate;
    
    // invariant: rate = man*2^(exp-31)
    while (!(man & (1<<31))) {
      exp = exp - 1;
      man = man<<1;
    }
    
    // man has top bit set
    // rate = (2^31+(man-2^31))*2^(exp-31)
    // rate = (1+(man-2^31)/2^31)*2^exp
    man = man<<1;
    man &= 0xffffffffU; // a nop on 32-bit systems
    // rate = (1+man/2^32)*2^exp
    
    // exp is in the range 0 to 31, man is in the range 0 to 2^32-1
    // time to lose significance... we want m in the range 0 to 2^9-1
    // rounding presents a minor problem... we first decide which way
    // we are rounding (based on given rounding direction and possibly
    // the bits of the mantissa that are to be discarded).
    
    switch (r) {
      case round_down: {
	// just truncate
	man = man>>(32-9);
	break;
      }
      case round_up: {
	// check all bits that we are discarding
	if (man & (~0U>>9)) {
	  man = (man>>(32-9)) + 1;
	  if (man == (1<<9)) {
	    // no need to check for round up outside of range
	    man = 0;
	    exp += 1;
	  }
	} else {
	  man = (man>>(32-9));
	}
	break;
      }
      case round_nearest: {
	// check msb that we are discarding
	if (man & (1<<(32-9-1))) {
	  man = (man>>(32-9)) + 1;
	  if (man == (1<<9)) {
	    // no need to check for round up outside of range
	    man = 0;
	    exp += 1;
	  }
	} else {
	  man = (man>>(32-9));
	}
	break;
      }
    }
    
  } else {
    // zero rate - not representable
    
    if (r == round_down) {
      return -EINVAL;
    } else {
      exp = 0;
      man = 0;
    }
    
  }
  
  PRINTD (DBG_QOS, "rate: man=%u, exp=%hu", man, exp);
  
  if (bits)
    *bits = /* (1<<14) | */ (exp<<9) | man;
  
  if (actual)
    *actual = (exp >= 9)
      ? (1 << exp) + (man << (exp-9))
      : (1 << exp) + ((man + (1<<(9-exp-1))) >> (9-exp));
  
  return 0;
}
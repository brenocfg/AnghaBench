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
typedef  int u8 ;
typedef  int u64 ;
typedef  int u32 ;
typedef  int i64 ;

/* Variables and functions */
 scalar_t__ CORRUPT_DB ; 
 int FOUR_BYTE_UINT (int const*) ; 
 int ONE_BYTE_INT (int const*) ; 
 int THREE_BYTE_INT (int const*) ; 
 int TWO_BYTE_INT (int const*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  testcase (int const) ; 

__attribute__((used)) static i64 vdbeRecordDecodeInt(u32 serial_type, const u8 *aKey){
  u32 y;
  assert( CORRUPT_DB || (serial_type>=1 && serial_type<=9 && serial_type!=7) );
  switch( serial_type ){
    case 0:
    case 1:
      testcase( aKey[0]&0x80 );
      return ONE_BYTE_INT(aKey);
    case 2:
      testcase( aKey[0]&0x80 );
      return TWO_BYTE_INT(aKey);
    case 3:
      testcase( aKey[0]&0x80 );
      return THREE_BYTE_INT(aKey);
    case 4: {
      testcase( aKey[0]&0x80 );
      y = FOUR_BYTE_UINT(aKey);
      return (i64)*(int*)&y;
    }
    case 5: {
      testcase( aKey[0]&0x80 );
      return FOUR_BYTE_UINT(aKey+2) + (((i64)1)<<32)*TWO_BYTE_INT(aKey);
    }
    case 6: {
      u64 x = FOUR_BYTE_UINT(aKey);
      testcase( aKey[0]&0x80 );
      x = (x<<32) | FOUR_BYTE_UINT(aKey+4);
      return (i64)*(i64*)&x;
    }
  }

  return (serial_type - 8);
}
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
typedef  int u16 ;
struct TYPE_4__ {int flags; } ;
typedef  TYPE_1__ Mem ;

/* Variables and functions */
 int MEM_Blob ; 
 int MEM_Int ; 
 int MEM_IntReal ; 
 int MEM_Real ; 
 int MEM_Str ; 
 int computeNumericType (TYPE_1__*) ; 
 int /*<<< orphan*/  testcase (int) ; 

__attribute__((used)) static u16 numericType(Mem *pMem){
  if( pMem->flags & (MEM_Int|MEM_Real|MEM_IntReal) ){
    testcase( pMem->flags & MEM_Int );
    testcase( pMem->flags & MEM_Real );
    testcase( pMem->flags & MEM_IntReal );
    return pMem->flags & (MEM_Int|MEM_Real|MEM_IntReal);
  }
  if( pMem->flags & (MEM_Str|MEM_Blob) ){
    testcase( pMem->flags & MEM_Str );
    testcase( pMem->flags & MEM_Blob );
    return computeNumericType(pMem);
  }
  return 0;
}
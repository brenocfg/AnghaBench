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
typedef  int U32 ;

/* Variables and functions */
 int /*<<< orphan*/  BMK_benchHash (int /*<<< orphan*/ ,char*,char const*,size_t) ; 
 int /*<<< orphan*/  DISPLAY (char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  localXXH32 ; 
 int /*<<< orphan*/  localXXH64 ; 

__attribute__((used)) static int BMK_benchMem(const void* buffer, size_t bufferSize, U32 specificTest)
{
    assert((((size_t)buffer) & 8) == 0);  /* ensure alignment */

    /* XXH32 bench */
    if ((specificTest==0) | (specificTest==1))
        BMK_benchHash(localXXH32, "XXH32", buffer, bufferSize);

    /* Bench XXH32 on Unaligned input */
    if ((specificTest==0) | (specificTest==2))
        BMK_benchHash(localXXH32, "XXH32 unaligned", ((const char*)buffer)+1, bufferSize);

    /* Bench XXH64 */
    if ((specificTest==0) | (specificTest==3))
        BMK_benchHash(localXXH64, "XXH64", buffer, bufferSize);

    /* Bench XXH64 on Unaligned input */
    if ((specificTest==0) | (specificTest==4))
        BMK_benchHash(localXXH64, "XXH64 unaligned", ((const char*)buffer)+3, bufferSize);

    if (specificTest > 4) {
        DISPLAY("benchmark mode invalid \n");
        return 1;
    }
    return 0;
}
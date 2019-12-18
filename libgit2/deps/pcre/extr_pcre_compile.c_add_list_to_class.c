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
typedef  int /*<<< orphan*/  pcre_uint8 ;
typedef  unsigned int pcre_uint32 ;
typedef  int /*<<< orphan*/  pcre_uchar ;
typedef  int /*<<< orphan*/  compile_data ;

/* Variables and functions */
 unsigned int const NOTACHAR ; 
 scalar_t__ add_to_class (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int,int /*<<< orphan*/ *,unsigned int const,unsigned int const) ; 

__attribute__((used)) static int
add_list_to_class(pcre_uint8 *classbits, pcre_uchar **uchardptr, int options,
  compile_data *cd, const pcre_uint32 *p, unsigned int except)
{
int n8 = 0;
while (p[0] < NOTACHAR)
  {
  int n = 0;
  if (p[0] != except)
    {
    while(p[n+1] == p[0] + n + 1) n++;
    n8 += add_to_class(classbits, uchardptr, options, cd, p[0], p[n]);
    }
  p += n + 1;
  }
return n8;
}
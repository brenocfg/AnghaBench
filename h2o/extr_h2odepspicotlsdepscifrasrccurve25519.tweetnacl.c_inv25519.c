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
typedef  int /*<<< orphan*/ * gf ;

/* Variables and functions */
 int /*<<< orphan*/  mul (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  sqr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void inv25519(gf o, const gf i)
{
  gf c;
  int a;
  for (a = 0; a < 16; a++)
    c[a] = i[a];
  
  for (a = 253; a >= 0; a--)
  {
    sqr(c, c);
    if(a != 2 && a != 4)
      mul(c, c, i);
  }

  for (a = 0; a < 16; a++)
    o[a] = c[a];
}
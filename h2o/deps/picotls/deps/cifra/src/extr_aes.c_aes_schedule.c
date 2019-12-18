#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t uint32_t ;
struct TYPE_3__ {int rounds; size_t* ks; } ;
typedef  TYPE_1__ cf_aes_context ;

/* Variables and functions */
 int AES_BLOCKSZ ; 
 int /*<<< orphan*/  S ; 
 size_t read32_be (int /*<<< orphan*/  const*) ; 
 size_t rot_word (size_t) ; 
 size_t round_constant (size_t) ; 
 size_t sub_word (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void aes_schedule(cf_aes_context *ctx, const uint8_t *key, size_t nkey)
{
  size_t i,
         nb = AES_BLOCKSZ / 4,
         nk = nkey / 4,
         n = nb * (ctx->rounds + 1);
  uint32_t *w = ctx->ks;

  /* First words are just the key. */
  for (i = 0; i < nk; i++)
  {
    w[i] = read32_be(key + i * 4);
  }

  uint32_t i_div_nk = 1;
  uint32_t i_mod_nk = 0;

  for (; i < n; i++, i_mod_nk++)
  {
    uint32_t temp = w[i - 1];
    
    if (i_mod_nk == nk)
    {
      i_div_nk++;
      i_mod_nk = 0;
    }

    if (i_mod_nk == 0)
      temp = sub_word(rot_word(temp), S) ^ round_constant(i_div_nk);
    else if (nk > 6 && i_mod_nk == 4)
      temp = sub_word(temp, S);

    w[i] = w[i - nk] ^ temp;
  }
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wordlist_hash ;
typedef  int /*<<< orphan*/  wordlist_autohex_disable ;
typedef  int /*<<< orphan*/  wordlist2_hash ;
typedef  int /*<<< orphan*/  wordlist1_hash ;
typedef  int /*<<< orphan*/  veracrypt_pim_stop ;
typedef  int /*<<< orphan*/  veracrypt_pim_start ;
struct TYPE_8__ {int attack_mode; int skip; int limit; int hex_salt; int hccapx_message_pair; int nonce_error_corrections; int veracrypt_pim_start; int veracrypt_pim_stop; int hex_wordlist; int wordlist_autohex_disable; char* encoding_from; char* encoding_to; char* rule_buf_l; char* rule_buf_r; int loopback; int hex_charset; int markov_classic; int markov_disable; int markov_threshold; char* custom_charset_1; char* custom_charset_2; char* custom_charset_3; char* custom_charset_4; int /*<<< orphan*/  markov_hcstat2; int /*<<< orphan*/  brain_session; } ;
typedef  TYPE_1__ user_options_t ;
typedef  char u64 ;
typedef  int /*<<< orphan*/  const u32 ;
struct TYPE_9__ {char const* kernel_rules_buf; int kernel_rules_cnt; scalar_t__ dict; } ;
typedef  TYPE_2__ straight_ctx_t ;
typedef  int /*<<< orphan*/  skip ;
typedef  int /*<<< orphan*/  nonce_error_corrections ;
struct TYPE_10__ {char* mask; } ;
typedef  TYPE_3__ mask_ctx_t ;
typedef  int /*<<< orphan*/  markov_threshold ;
typedef  int /*<<< orphan*/  markov_disable ;
typedef  int /*<<< orphan*/  markov_classic ;
typedef  int /*<<< orphan*/  loopback ;
typedef  int /*<<< orphan*/  limit ;
typedef  int /*<<< orphan*/  kernel_rule_t ;
typedef  int /*<<< orphan*/  hex_wordlist ;
typedef  int /*<<< orphan*/  hex_salt ;
typedef  int /*<<< orphan*/  hex_charset ;
typedef  int /*<<< orphan*/  hccapx_message_pair ;
struct TYPE_11__ {int hash_mode; } ;
typedef  TYPE_4__ hashconfig_t ;
struct TYPE_12__ {TYPE_1__* user_options; TYPE_2__* straight_ctx; TYPE_3__* mask_ctx; TYPE_4__* hashconfig; TYPE_6__* combinator_ctx; } ;
typedef  TYPE_5__ hashcat_ctx_t ;
typedef  int /*<<< orphan*/  hash_mode ;
struct TYPE_13__ {scalar_t__ dict2; scalar_t__ dict1; } ;
typedef  TYPE_6__ combinator_ctx_t ;
typedef  int /*<<< orphan*/  attack_mode ;
typedef  int /*<<< orphan*/  XXH64_state_t ;

/* Variables and functions */
 int ATTACK_MODE_BF ; 
 int ATTACK_MODE_COMBI ; 
 int ATTACK_MODE_HYBRID1 ; 
 int ATTACK_MODE_HYBRID2 ; 
 int ATTACK_MODE_STRAIGHT ; 
 int /*<<< orphan*/ * XXH64_createState () ; 
 int /*<<< orphan*/  XXH64_digest (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XXH64_freeState (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XXH64_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XXH64_update (int /*<<< orphan*/ *,...) ; 
 char brain_compute_attack_wordlist (scalar_t__) ; 
 char* filename_from_filepath (int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 

u32 brain_compute_attack (hashcat_ctx_t *hashcat_ctx)
{
  const combinator_ctx_t *combinator_ctx = hashcat_ctx->combinator_ctx;
  const hashconfig_t     *hashconfig     = hashcat_ctx->hashconfig;
  const mask_ctx_t       *mask_ctx       = hashcat_ctx->mask_ctx;
  const straight_ctx_t   *straight_ctx   = hashcat_ctx->straight_ctx;
  const user_options_t   *user_options   = hashcat_ctx->user_options;

  XXH64_state_t *state = XXH64_createState ();

  XXH64_reset (state, user_options->brain_session);

  const int hash_mode   = hashconfig->hash_mode;
  const int attack_mode = user_options->attack_mode;

  XXH64_update (state, &hash_mode,   sizeof (hash_mode));
  XXH64_update (state, &attack_mode, sizeof (attack_mode));

  const int skip  = user_options->skip;
  const int limit = user_options->limit;

  XXH64_update (state, &skip,  sizeof (skip));
  XXH64_update (state, &limit, sizeof (limit));

  const int hex_salt = user_options->hex_salt;

  XXH64_update (state, &hex_salt, sizeof (hex_salt));

  const int hccapx_message_pair = user_options->hccapx_message_pair;

  XXH64_update (state, &hccapx_message_pair, sizeof (hccapx_message_pair));

  const int nonce_error_corrections = user_options->nonce_error_corrections;

  XXH64_update (state, &nonce_error_corrections, sizeof (nonce_error_corrections));

  const int veracrypt_pim_start = user_options->veracrypt_pim_start;

  XXH64_update (state, &veracrypt_pim_start, sizeof (veracrypt_pim_start));

  const int veracrypt_pim_stop = user_options->veracrypt_pim_stop;

  XXH64_update (state, &veracrypt_pim_stop, sizeof (veracrypt_pim_stop));

  if (user_options->attack_mode == ATTACK_MODE_STRAIGHT)
  {
    if (straight_ctx->dict)
    {
      const u64 wordlist_hash = brain_compute_attack_wordlist (straight_ctx->dict);

      XXH64_update (state, &wordlist_hash, sizeof (wordlist_hash));
    }

    const int hex_wordlist = user_options->hex_wordlist;

    XXH64_update (state, &hex_wordlist, sizeof (hex_wordlist));

    const int wordlist_autohex_disable = user_options->wordlist_autohex_disable;

    XXH64_update (state, &wordlist_autohex_disable, sizeof (wordlist_autohex_disable));

    if (user_options->encoding_from)
    {
      const char *encoding_from = user_options->encoding_from;

      XXH64_update (state, encoding_from, strlen (encoding_from));
    }

    if (user_options->encoding_to)
    {
      const char *encoding_to = user_options->encoding_to;

      XXH64_update (state, encoding_to, strlen (encoding_to));
    }

    if (user_options->rule_buf_l)
    {
      const char *rule_buf_l = user_options->rule_buf_l;

      XXH64_update (state, rule_buf_l, strlen (rule_buf_l));
    }

    if (user_options->rule_buf_r)
    {
      const char *rule_buf_r = user_options->rule_buf_r;

      XXH64_update (state, rule_buf_r, strlen (rule_buf_r));
    }

    const int loopback = user_options->loopback;

    XXH64_update (state, &loopback, sizeof (loopback));

    XXH64_update (state, straight_ctx->kernel_rules_buf, straight_ctx->kernel_rules_cnt * sizeof (kernel_rule_t));
  }
  else if (user_options->attack_mode == ATTACK_MODE_COMBI)
  {
    const u64 wordlist1_hash = brain_compute_attack_wordlist (combinator_ctx->dict1);
    const u64 wordlist2_hash = brain_compute_attack_wordlist (combinator_ctx->dict2);

    XXH64_update (state, &wordlist1_hash, sizeof (wordlist1_hash));
    XXH64_update (state, &wordlist2_hash, sizeof (wordlist2_hash));

    const int hex_wordlist = user_options->hex_wordlist;

    XXH64_update (state, &hex_wordlist, sizeof (hex_wordlist));

    const int wordlist_autohex_disable = user_options->wordlist_autohex_disable;

    XXH64_update (state, &wordlist_autohex_disable, sizeof (wordlist_autohex_disable));

    if (user_options->encoding_from)
    {
      const char *encoding_from = user_options->encoding_from;

      XXH64_update (state, encoding_from, strlen (encoding_from));
    }

    if (user_options->encoding_to)
    {
      const char *encoding_to = user_options->encoding_to;

      XXH64_update (state, encoding_to, strlen (encoding_to));
    }

    if (user_options->rule_buf_l)
    {
      const char *rule_buf_l = user_options->rule_buf_l;

      XXH64_update (state, rule_buf_l, strlen (rule_buf_l));
    }

    if (user_options->rule_buf_r)
    {
      const char *rule_buf_r = user_options->rule_buf_r;

      XXH64_update (state, rule_buf_r, strlen (rule_buf_r));
    }
  }
  else if (user_options->attack_mode == ATTACK_MODE_BF)
  {
    const char *mask = mask_ctx->mask;

    XXH64_update (state, mask, strlen (mask));

    const int hex_charset = user_options->hex_charset;

    XXH64_update (state, &hex_charset, sizeof (hex_charset));

    const int markov_classic   = user_options->markov_classic;
    const int markov_disable   = user_options->markov_disable;
    const int markov_threshold = user_options->markov_threshold;

    XXH64_update (state, &markov_classic,   sizeof (markov_classic));
    XXH64_update (state, &markov_disable,   sizeof (markov_disable));
    XXH64_update (state, &markov_threshold, sizeof (markov_threshold));

    if (user_options->markov_hcstat2)
    {
      const char *markov_hcstat2 = filename_from_filepath (user_options->markov_hcstat2);

      XXH64_update (state, markov_hcstat2, strlen (markov_hcstat2));
    }

    if (user_options->custom_charset_1)
    {
      const char *custom_charset_1 = user_options->custom_charset_1;

      XXH64_update (state, custom_charset_1, strlen (custom_charset_1));
    }

    if (user_options->custom_charset_2)
    {
      const char *custom_charset_2 = user_options->custom_charset_2;

      XXH64_update (state, custom_charset_2, strlen (custom_charset_2));
    }

    if (user_options->custom_charset_3)
    {
      const char *custom_charset_3 = user_options->custom_charset_3;

      XXH64_update (state, custom_charset_3, strlen (custom_charset_3));
    }

    if (user_options->custom_charset_4)
    {
      const char *custom_charset_4 = user_options->custom_charset_4;

      XXH64_update (state, custom_charset_4, strlen (custom_charset_4));
    }
  }
  else if (user_options->attack_mode == ATTACK_MODE_HYBRID1)
  {
    const u64 wordlist_hash = brain_compute_attack_wordlist (straight_ctx->dict);

    XXH64_update (state, &wordlist_hash, sizeof (wordlist_hash));

    const char *mask = mask_ctx->mask;

    XXH64_update (state, mask, strlen (mask));

    const int hex_charset = user_options->hex_charset;

    XXH64_update (state, &hex_charset, sizeof (hex_charset));

    const int markov_classic   = user_options->markov_classic;
    const int markov_disable   = user_options->markov_disable;
    const int markov_threshold = user_options->markov_threshold;

    XXH64_update (state, &markov_classic,   sizeof (markov_classic));
    XXH64_update (state, &markov_disable,   sizeof (markov_disable));
    XXH64_update (state, &markov_threshold, sizeof (markov_threshold));

    if (user_options->markov_hcstat2)
    {
      const char *markov_hcstat2 = filename_from_filepath (user_options->markov_hcstat2);

      XXH64_update (state, markov_hcstat2, strlen (markov_hcstat2));
    }

    if (user_options->custom_charset_1)
    {
      const char *custom_charset_1 = user_options->custom_charset_1;

      XXH64_update (state, custom_charset_1, strlen (custom_charset_1));
    }

    if (user_options->custom_charset_2)
    {
      const char *custom_charset_2 = user_options->custom_charset_2;

      XXH64_update (state, custom_charset_2, strlen (custom_charset_2));
    }

    if (user_options->custom_charset_3)
    {
      const char *custom_charset_3 = user_options->custom_charset_3;

      XXH64_update (state, custom_charset_3, strlen (custom_charset_3));
    }

    if (user_options->custom_charset_4)
    {
      const char *custom_charset_4 = user_options->custom_charset_4;

      XXH64_update (state, custom_charset_4, strlen (custom_charset_4));
    }

    const int hex_wordlist = user_options->hex_wordlist;

    XXH64_update (state, &hex_wordlist, sizeof (hex_wordlist));

    const int wordlist_autohex_disable = user_options->wordlist_autohex_disable;

    XXH64_update (state, &wordlist_autohex_disable, sizeof (wordlist_autohex_disable));

    if (user_options->encoding_from)
    {
      const char *encoding_from = user_options->encoding_from;

      XXH64_update (state, encoding_from, strlen (encoding_from));
    }

    if (user_options->encoding_to)
    {
      const char *encoding_to = user_options->encoding_to;

      XXH64_update (state, encoding_to, strlen (encoding_to));
    }

    if (user_options->rule_buf_l)
    {
      const char *rule_buf_l = user_options->rule_buf_l;

      XXH64_update (state, rule_buf_l, strlen (rule_buf_l));
    }

    if (user_options->rule_buf_r)
    {
      const char *rule_buf_r = user_options->rule_buf_r;

      XXH64_update (state, rule_buf_r, strlen (rule_buf_r));
    }
  }
  else if (user_options->attack_mode == ATTACK_MODE_HYBRID2)
  {
    const char *mask = mask_ctx->mask;

    XXH64_update (state, mask, strlen (mask));

    const u64 wordlist_hash = brain_compute_attack_wordlist (straight_ctx->dict);

    XXH64_update (state, &wordlist_hash, sizeof (wordlist_hash));

    const int hex_charset = user_options->hex_charset;

    XXH64_update (state, &hex_charset, sizeof (hex_charset));

    const int markov_classic   = user_options->markov_classic;
    const int markov_disable   = user_options->markov_disable;
    const int markov_threshold = user_options->markov_threshold;

    XXH64_update (state, &markov_classic,   sizeof (markov_classic));
    XXH64_update (state, &markov_disable,   sizeof (markov_disable));
    XXH64_update (state, &markov_threshold, sizeof (markov_threshold));

    if (user_options->markov_hcstat2)
    {
      const char *markov_hcstat2 = filename_from_filepath (user_options->markov_hcstat2);

      XXH64_update (state, markov_hcstat2, strlen (markov_hcstat2));
    }

    if (user_options->custom_charset_1)
    {
      const char *custom_charset_1 = user_options->custom_charset_1;

      XXH64_update (state, custom_charset_1, strlen (custom_charset_1));
    }

    if (user_options->custom_charset_2)
    {
      const char *custom_charset_2 = user_options->custom_charset_2;

      XXH64_update (state, custom_charset_2, strlen (custom_charset_2));
    }

    if (user_options->custom_charset_3)
    {
      const char *custom_charset_3 = user_options->custom_charset_3;

      XXH64_update (state, custom_charset_3, strlen (custom_charset_3));
    }

    if (user_options->custom_charset_4)
    {
      const char *custom_charset_4 = user_options->custom_charset_4;

      XXH64_update (state, custom_charset_4, strlen (custom_charset_4));
    }

    const int hex_wordlist = user_options->hex_wordlist;

    XXH64_update (state, &hex_wordlist, sizeof (hex_wordlist));

    const int wordlist_autohex_disable = user_options->wordlist_autohex_disable;

    XXH64_update (state, &wordlist_autohex_disable, sizeof (wordlist_autohex_disable));

    if (user_options->encoding_from)
    {
      const char *encoding_from = user_options->encoding_from;

      XXH64_update (state, encoding_from, strlen (encoding_from));
    }

    if (user_options->encoding_to)
    {
      const char *encoding_to = user_options->encoding_to;

      XXH64_update (state, encoding_to, strlen (encoding_to));
    }

    if (user_options->rule_buf_l)
    {
      const char *rule_buf_l = user_options->rule_buf_l;

      XXH64_update (state, rule_buf_l, strlen (rule_buf_l));
    }

    if (user_options->rule_buf_r)
    {
      const char *rule_buf_r = user_options->rule_buf_r;

      XXH64_update (state, rule_buf_r, strlen (rule_buf_r));
    }
  }

  const u32 brain_attack = (const u32) XXH64_digest (state);

  XXH64_freeState (state);

  return brain_attack;
}
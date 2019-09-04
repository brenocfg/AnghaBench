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
typedef  int /*<<< orphan*/  const u64 ;
typedef  int /*<<< orphan*/  XXH64_state_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/ * XXH64_createState () ; 
 int /*<<< orphan*/  const XXH64_digest (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XXH64_freeState (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XXH64_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XXH64_update (int /*<<< orphan*/ *,char*,size_t const) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 size_t fread (char*,int,int,int /*<<< orphan*/ *) ; 

u64 brain_compute_attack_wordlist (const char *filename)
{
  XXH64_state_t *state = XXH64_createState ();

  XXH64_reset (state, 0);

  #define FBUFSZ 8192

  char buf[FBUFSZ];

  FILE *fd = fopen (filename, "rb");

  while (!feof (fd))
  {
    const size_t nread = fread (buf, 1, FBUFSZ, fd);

    XXH64_update (state, buf, nread);
  }

  fclose (fd);

  const u64 hash = XXH64_digest (state);

  XXH64_freeState (state);

  return hash;
}
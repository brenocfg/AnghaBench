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
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  rnd ;

/* Variables and functions */
 scalar_t__ ERR_get_error () ; 
 int IVSZ ; 
 int KEYSZ ; 
 scalar_t__ RAND_bytes (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  RSBUFSZ ; 
 int /*<<< orphan*/  _rs_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  _rs_rekey (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  explicit_bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fatal (char*,unsigned long) ; 
 int /*<<< orphan*/  getrnd (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rs_buf ; 
 int rs_count ; 
 scalar_t__ rs_have ; 
 int rs_initialized ; 

__attribute__((used)) static void
_rs_stir(void)
{
	u_char rnd[KEYSZ + IVSZ];

#ifdef WITH_OPENSSL
	if (RAND_bytes(rnd, sizeof(rnd)) <= 0)
		fatal("Couldn't obtain random bytes (error 0x%lx)",
		    (unsigned long)ERR_get_error());
#else
	getrnd(rnd, sizeof(rnd));
#endif

	if (!rs_initialized) {
		rs_initialized = 1;
		_rs_init(rnd, sizeof(rnd));
	} else
		_rs_rekey(rnd, sizeof(rnd));
	explicit_bzero(rnd, sizeof(rnd));

	/* invalidate rs_buf */
	rs_have = 0;
	memset(rs_buf, 0, RSBUFSZ);

	rs_count = 1600000;
}
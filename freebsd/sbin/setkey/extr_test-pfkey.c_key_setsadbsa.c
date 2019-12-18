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
struct sadb_sa {int sadb_sa_replay; scalar_t__ sadb_sa_flags; int /*<<< orphan*/  sadb_sa_encrypt; int /*<<< orphan*/  sadb_sa_auth; scalar_t__ sadb_sa_state; int /*<<< orphan*/  sadb_sa_spi; int /*<<< orphan*/  sadb_sa_exttype; int /*<<< orphan*/  sadb_sa_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  PFKEY_UNIT64 (int) ; 
 int /*<<< orphan*/  SADB_AALG_MD5HMAC ; 
 int /*<<< orphan*/  SADB_EALG_DESCBC ; 
 int /*<<< orphan*/  SADB_EXT_SA ; 
 int /*<<< orphan*/  htonl (int) ; 
 scalar_t__ m_buf ; 
 scalar_t__ m_len ; 
 int /*<<< orphan*/  memcpy (scalar_t__,struct sadb_sa*,int) ; 

void
key_setsadbsa()
{
	struct sadb_sa m_sa;

	m_sa.sadb_sa_len = PFKEY_UNIT64(sizeof(struct sadb_sa));
	m_sa.sadb_sa_exttype = SADB_EXT_SA;
	m_sa.sadb_sa_spi = htonl(0x12345678);
	m_sa.sadb_sa_replay = 4;
	m_sa.sadb_sa_state = 0;
	m_sa.sadb_sa_auth = SADB_AALG_MD5HMAC;
	m_sa.sadb_sa_encrypt = SADB_EALG_DESCBC;
	m_sa.sadb_sa_flags = 0;

	memcpy(m_buf + m_len, &m_sa, sizeof(struct sadb_sa));
	m_len += sizeof(struct sadb_sa);

	return;
}
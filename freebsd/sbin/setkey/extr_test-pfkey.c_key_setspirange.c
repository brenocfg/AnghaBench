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
struct sadb_spirange {int sadb_spirange_min; int sadb_spirange_max; scalar_t__ sadb_spirange_reserved; int /*<<< orphan*/  sadb_spirange_exttype; int /*<<< orphan*/  sadb_spirange_len; } ;
typedef  int /*<<< orphan*/  m_spi ;

/* Variables and functions */
 int /*<<< orphan*/  PFKEY_UNIT64 (int) ; 
 int /*<<< orphan*/  SADB_EXT_SPIRANGE ; 
 scalar_t__ m_buf ; 
 scalar_t__ m_len ; 
 int /*<<< orphan*/  memcpy (scalar_t__,struct sadb_spirange*,int) ; 

void
key_setspirange()
{
	struct sadb_spirange m_spi;

	m_spi.sadb_spirange_len = PFKEY_UNIT64(sizeof(m_spi));
	m_spi.sadb_spirange_exttype = SADB_EXT_SPIRANGE;
	m_spi.sadb_spirange_min = 0x00001000;
	m_spi.sadb_spirange_max = 0x00002000;
	m_spi.sadb_spirange_reserved = 0;

	memcpy(m_buf + m_len, &m_spi, sizeof(struct sadb_spirange));
	m_len += sizeof(struct sadb_spirange);

	return;
}
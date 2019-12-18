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
struct mbuf {int dummy; } ;
typedef  int /*<<< orphan*/  gss_qop_t ;
typedef  int /*<<< orphan*/  gss_ctx_id_t ;
typedef  TYPE_1__* gss_buffer_t ;
struct TYPE_4__ {int /*<<< orphan*/  value; int /*<<< orphan*/  length; } ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 scalar_t__ GSS_S_NO_CONTEXT ; 
 scalar_t__ KGSS_VERIFY_MIC (int /*<<< orphan*/  const,scalar_t__*,struct mbuf*,struct mbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MCLGET (struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MGET (struct mbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLEN ; 
 int /*<<< orphan*/  MT_DATA ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  m_append (struct mbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 

OM_uint32
gss_verify_mic(OM_uint32 *minor_status,
    const gss_ctx_id_t ctx,
    const gss_buffer_t message_buffer,
    const gss_buffer_t token_buffer,
    gss_qop_t *qop_state)
{
	OM_uint32 maj_stat;
	struct mbuf *m, *mic;

	if (!ctx) {
		*minor_status = 0;
		return (GSS_S_NO_CONTEXT);
	}

	MGET(m, M_WAITOK, MT_DATA);
	if (message_buffer->length > MLEN)
		MCLGET(m, M_WAITOK);
	m_append(m, message_buffer->length, message_buffer->value);

	MGET(mic, M_WAITOK, MT_DATA);
	if (token_buffer->length > MLEN)
		MCLGET(mic, M_WAITOK);
	m_append(mic, token_buffer->length, token_buffer->value);

	maj_stat = KGSS_VERIFY_MIC(ctx, minor_status, m, mic, qop_state);

	m_freem(m);
	m_freem(mic);

	return (maj_stat);
}
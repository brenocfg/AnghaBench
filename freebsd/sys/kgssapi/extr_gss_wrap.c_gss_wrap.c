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
 scalar_t__ GSS_S_COMPLETE ; 
 scalar_t__ GSS_S_NO_CONTEXT ; 
 scalar_t__ KGSS_WRAP (int /*<<< orphan*/  const,scalar_t__*,int,int /*<<< orphan*/ ,struct mbuf**,int*) ; 
 int /*<<< orphan*/  MCLGET (struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MGET (struct mbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLEN ; 
 int /*<<< orphan*/  MT_DATA ; 
 int /*<<< orphan*/  M_GSSAPI ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  m_append (struct mbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_copydata (struct mbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  m_length (struct mbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

OM_uint32
gss_wrap(OM_uint32 *minor_status,
    const gss_ctx_id_t ctx,
    int conf_req_flag,
    gss_qop_t qop_req,
    const gss_buffer_t input_message_buffer,
    int *conf_state,
    gss_buffer_t output_message_buffer)
{
	OM_uint32 maj_stat;
	struct mbuf *m;

	if (!ctx) {
		*minor_status = 0;
		return (GSS_S_NO_CONTEXT);
	}

	MGET(m, M_WAITOK, MT_DATA);
	if (input_message_buffer->length > MLEN)
		MCLGET(m, M_WAITOK);
	m_append(m, input_message_buffer->length, input_message_buffer->value);

	maj_stat = KGSS_WRAP(ctx, minor_status, conf_req_flag, qop_req,
	    &m, conf_state);

	/*
	 * On success, m is the wrapped message, on failure, m is
	 * freed.
	 */
	if (maj_stat == GSS_S_COMPLETE) {
		output_message_buffer->length = m_length(m, NULL);
		output_message_buffer->value =
			malloc(output_message_buffer->length,
			    M_GSSAPI, M_WAITOK);
		m_copydata(m, 0, output_message_buffer->length,
		    output_message_buffer->value);
		m_freem(m);
	}

	return (maj_stat);
}
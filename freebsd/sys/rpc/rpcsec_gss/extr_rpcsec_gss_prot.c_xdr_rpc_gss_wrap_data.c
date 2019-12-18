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
typedef  scalar_t__ u_int ;
struct mbuf {int dummy; } ;
typedef  scalar_t__ rpc_gss_service_t ;
typedef  int /*<<< orphan*/  gss_qop_t ;
typedef  int /*<<< orphan*/  gss_ctx_id_t ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GSS_S_COMPLETE ; 
 scalar_t__ RNDUP (scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ gss_get_mic_mbuf (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mbuf*,struct mbuf**) ; 
 scalar_t__ gss_wrap_mbuf (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mbuf**,int*) ; 
 int /*<<< orphan*/  m_append (struct mbuf*,scalar_t__,char*) ; 
 int /*<<< orphan*/  m_cat (struct mbuf*,struct mbuf*) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 scalar_t__ m_length (struct mbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_uint32 (struct mbuf**,scalar_t__) ; 
 int /*<<< orphan*/  rpc_gss_log_debug (char*) ; 
 int /*<<< orphan*/  rpc_gss_log_status (char*,int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 scalar_t__ rpc_gss_svc_integrity ; 
 scalar_t__ rpc_gss_svc_privacy ; 

bool_t
xdr_rpc_gss_wrap_data(struct mbuf **argsp,
		      gss_ctx_id_t ctx, gss_qop_t qop,
		      rpc_gss_service_t svc, u_int seq)
{
	struct mbuf	*args, *mic;
	OM_uint32	maj_stat, min_stat;
	int		conf_state;
	u_int		len;
	static char	zpad[4];

	args = *argsp;

	/*
	 * Prepend the sequence number before calling gss_get_mic or gss_wrap.
	 */
	put_uint32(&args, seq);
	len = m_length(args, NULL);

	if (svc == rpc_gss_svc_integrity) {
		/* Checksum rpc_gss_data_t. */
		maj_stat = gss_get_mic_mbuf(&min_stat, ctx, qop, args, &mic);
		if (maj_stat != GSS_S_COMPLETE) {
			rpc_gss_log_debug("gss_get_mic failed");
			m_freem(args);
			return (FALSE);
		}

		/*
		 * Marshal databody_integ. Note that since args is
		 * already RPC encoded, there will be no padding.
		 */
		put_uint32(&args, len);

		/*
		 * Marshal checksum. This is likely to need padding.
		 */
		len = m_length(mic, NULL);
		put_uint32(&mic, len);
		if (len != RNDUP(len)) {
			m_append(mic, RNDUP(len) - len, zpad);
		}

		/*
		 * Concatenate databody_integ with checksum.
		 */
		m_cat(args, mic);
	} else if (svc == rpc_gss_svc_privacy) {
		/* Encrypt rpc_gss_data_t. */
		maj_stat = gss_wrap_mbuf(&min_stat, ctx, TRUE, qop,
		    &args, &conf_state);
		if (maj_stat != GSS_S_COMPLETE) {
			rpc_gss_log_status("gss_wrap", NULL,
			    maj_stat, min_stat);
			return (FALSE);
		}

		/*
		 *  Marshal databody_priv and deal with RPC padding.
		 */
		len = m_length(args, NULL);
		put_uint32(&args, len);
		if (len != RNDUP(len)) {
			m_append(args, RNDUP(len) - len, zpad);
		}
	}
	*argsp = args;
	return (TRUE);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct pcmchan_matrix {scalar_t__ channels; scalar_t__ id; int mask; int* offset; TYPE_1__* map; } ;
struct feed_matrix_info {int bps; TYPE_2__* matrix; int /*<<< orphan*/  out; int /*<<< orphan*/  in; } ;
struct TYPE_4__ {int* chn; int mul; int shift; } ;
struct TYPE_3__ {scalar_t__ type; size_t members; } ;

/* Variables and functions */
 scalar_t__ AFMT_CHANNEL (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int FEEDMATRIX_ATTN_SHIFT ; 
 scalar_t__ SND_CHN_MATRIX_1_0 ; 
 scalar_t__ SND_CHN_MATRIX_BEGIN ; 
 scalar_t__ SND_CHN_MATRIX_END ; 
 scalar_t__ SND_CHN_MAX ; 
 scalar_t__ SND_CHN_MIN ; 
 size_t SND_CHN_T_BEGIN ; 
 size_t SND_CHN_T_END ; 
 int SND_CHN_T_EOF ; 
 int SND_CHN_T_MASK_FC ; 
 size_t SND_CHN_T_MASK_FL ; 
 size_t SND_CHN_T_MASK_FR ; 
 scalar_t__ SND_CHN_T_MAX ; 
 int SND_CHN_T_NULL ; 
 scalar_t__ SND_CHN_T_STEP ; 
 int /*<<< orphan*/  feed_matrix_reset (struct feed_matrix_info*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
feed_matrix_setup(struct feed_matrix_info *info, struct pcmchan_matrix *m_in,
    struct pcmchan_matrix *m_out)
{
	uint32_t i, j, ch, in_mask, merge_mask;
	int mul, shift;


	if (info == NULL || m_in == NULL || m_out == NULL ||
	    AFMT_CHANNEL(info->in) != m_in->channels ||
	    AFMT_CHANNEL(info->out) != m_out->channels ||
	    m_in->channels < SND_CHN_MIN || m_in->channels > SND_CHN_MAX ||
	    m_out->channels < SND_CHN_MIN || m_out->channels > SND_CHN_MAX)
		return (EINVAL);

	feed_matrix_reset(info);

	/*
	 * If both in and out are part of standard matrix and identical, skip
	 * everything alltogether.
	 */
	if (m_in->id == m_out->id && !(m_in->id < SND_CHN_MATRIX_BEGIN ||
	    m_in->id > SND_CHN_MATRIX_END))
		return (0);

	/*
	 * Special case for mono input matrix. If the output supports
	 * possible 'center' channel, route it there. Otherwise, let it be
	 * matrixed to left/right.
	 */
	if (m_in->id == SND_CHN_MATRIX_1_0) {
		if (m_out->id == SND_CHN_MATRIX_1_0)
			in_mask = SND_CHN_T_MASK_FL;
		else if (m_out->mask & SND_CHN_T_MASK_FC)
			in_mask = SND_CHN_T_MASK_FC;
		else
			in_mask = SND_CHN_T_MASK_FL | SND_CHN_T_MASK_FR;
	} else
		in_mask = m_in->mask;

	/* Merge, reduce, expand all possibilites. */
	for (ch = SND_CHN_T_BEGIN; ch <= SND_CHN_T_END &&
	    m_out->map[ch].type != SND_CHN_T_MAX; ch += SND_CHN_T_STEP) {
		merge_mask = m_out->map[ch].members & in_mask;
		if (merge_mask == 0) {
			info->matrix[ch].chn[0] = SND_CHN_T_NULL;
			continue;
		}

		j = 0;
		for (i = SND_CHN_T_BEGIN; i <= SND_CHN_T_END;
		    i += SND_CHN_T_STEP) {
			if (merge_mask & (1 << i)) {
				if (m_in->offset[i] >= 0 &&
				    m_in->offset[i] < (int)m_in->channels)
					info->matrix[ch].chn[j++] =
					    m_in->offset[i] * info->bps;
				else {
					info->matrix[ch].chn[j++] =
					    SND_CHN_T_EOF;
					break;
				}
			}
		}

#define FEEDMATRIX_ATTN_SHIFT	16

		if (j > 1) {
			/*
			 * XXX For channel that require accumulation from
			 * multiple channels, apply a slight attenuation to
			 * avoid clipping.
			 */
			mul   = (1 << (FEEDMATRIX_ATTN_SHIFT - 1)) + 143 - j;
			shift = FEEDMATRIX_ATTN_SHIFT;
			while ((mul & 1) == 0 && shift > 0) {
				mul >>= 1;
				shift--;
			}
			info->matrix[ch].mul   = mul;
			info->matrix[ch].shift = shift;
		}
	}

#ifndef _KERNEL
	fprintf(stderr, "Total: %d\n", ch);

	for (i = 0; info->matrix[i].chn[0] != SND_CHN_T_EOF; i++) {
		fprintf(stderr, "%d: [", i);
		for (j = 0; info->matrix[i].chn[j] != SND_CHN_T_EOF; j++) {
			if (j != 0)
				fprintf(stderr, ", ");
			fprintf(stderr, "%d",
			    (info->matrix[i].chn[j] == SND_CHN_T_NULL) ?
			    0xffffffff : info->matrix[i].chn[j] / info->bps);
		}
		fprintf(stderr, "] attn: (x * %d) >> %d\n",
		    info->matrix[i].mul, info->matrix[i].shift);
	}
#endif

	return (0);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct host_bsq {int freebuf_count; struct buffer* freebuf; struct buffer* buffer; } ;
struct fore200e {int /*<<< orphan*/  state; TYPE_1__* bus; struct host_bsq** host_bsq; } ;
struct buffer {int scheme; int magn; int index; struct buffer* next; int /*<<< orphan*/  data; scalar_t__ supplied; } ;
struct TYPE_2__ {int /*<<< orphan*/  buffer_alignment; } ;

/* Variables and functions */
 int BUFFER_MAGN_NBR ; 
 int BUFFER_SCHEME_NBR ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DPRINTK (int,char*,int,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FORE200E_STATE_ALLOC_BUF ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  bsq_audit (int,struct host_bsq*,int,int) ; 
 scalar_t__ fore200e_chunk_alloc (struct fore200e*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fore200e_chunk_free (struct fore200e*,int /*<<< orphan*/ *) ; 
 int** fore200e_rx_buf_nbr ; 
 int** fore200e_rx_buf_size ; 
 struct buffer* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct buffer*) ; 

__attribute__((used)) static int fore200e_alloc_rx_buf(struct fore200e *fore200e)
{
    int scheme, magn, nbr, size, i;

    struct host_bsq* bsq;
    struct buffer*   buffer;

    for (scheme = 0; scheme < BUFFER_SCHEME_NBR; scheme++) {
	for (magn = 0; magn < BUFFER_MAGN_NBR; magn++) {

	    bsq = &fore200e->host_bsq[ scheme ][ magn ];

	    nbr  = fore200e_rx_buf_nbr[ scheme ][ magn ];
	    size = fore200e_rx_buf_size[ scheme ][ magn ];

	    DPRINTK(2, "rx buffers %d / %d are being allocated\n", scheme, magn);

	    /* allocate the array of receive buffers */
	    buffer = bsq->buffer = kcalloc(nbr, sizeof(struct buffer),
                                           GFP_KERNEL);

	    if (buffer == NULL)
		return -ENOMEM;

	    bsq->freebuf = NULL;

	    for (i = 0; i < nbr; i++) {

		buffer[ i ].scheme = scheme;
		buffer[ i ].magn   = magn;
#ifdef FORE200E_BSQ_DEBUG
		buffer[ i ].index  = i;
		buffer[ i ].supplied = 0;
#endif

		/* allocate the receive buffer body */
		if (fore200e_chunk_alloc(fore200e,
					 &buffer[ i ].data, size, fore200e->bus->buffer_alignment,
					 DMA_FROM_DEVICE) < 0) {
		    
		    while (i > 0)
			fore200e_chunk_free(fore200e, &buffer[ --i ].data);
		    kfree(buffer);
		    
		    return -ENOMEM;
		}

		/* insert the buffer into the free buffer list */
		buffer[ i ].next = bsq->freebuf;
		bsq->freebuf = &buffer[ i ];
	    }
	    /* all the buffers are free, initially */
	    bsq->freebuf_count = nbr;

#ifdef FORE200E_BSQ_DEBUG
	    bsq_audit(3, bsq, scheme, magn);
#endif
	}
    }

    fore200e->state = FORE200E_STATE_ALLOC_BUF;
    return 0;
}
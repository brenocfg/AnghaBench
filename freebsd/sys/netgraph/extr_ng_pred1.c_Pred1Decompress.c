#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
typedef  TYPE_1__* priv_p ;
typedef  int /*<<< orphan*/  node_p ;
struct TYPE_3__ {int* GuessTable; size_t Hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  HASH (int /*<<< orphan*/ ) ; 
 TYPE_1__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
Pred1Decompress(node_p node, u_char *source, u_char *dest, int slen, int dlen)
{
	const priv_p 	priv = NG_NODE_PRIVATE(node);
	int		i;
	u_char		flags, *orgdest;

	orgdest = dest;
	while (slen) {
		flags = *source++;
		slen--;
		for (i = 0; i < 8; i++, flags >>= 1) {
			if (dlen <= 0)
				return(-1);
			if (flags & 0x01)
				/* Guess correct */
				*dest = priv->GuessTable[priv->Hash];
			else {
				if (!slen)
					/* We seem to be really done -- cabo. */
					break;

				/* Guess wrong. */
				priv->GuessTable[priv->Hash] = *source;
				/* Read from source. */
				*dest = *source++;
				slen--;
			}
			HASH(*dest++);
			dlen--;
		}
	}
	return (dest - orgdest);
}
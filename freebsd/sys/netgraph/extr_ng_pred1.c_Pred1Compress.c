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
typedef  scalar_t__ u_char ;
typedef  TYPE_1__* priv_p ;
typedef  int /*<<< orphan*/  node_p ;
struct TYPE_3__ {scalar_t__* GuessTable; size_t Hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  HASH (int /*<<< orphan*/ ) ; 
 TYPE_1__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
Pred1Compress(node_p node, u_char *source, u_char *dest, int len)
{
	const priv_p 	priv = NG_NODE_PRIVATE(node);
	int		i;
	u_char		flags;
	u_char		*flagdest, *orgdest;

	orgdest = dest;
	while (len) {
		flagdest = dest++;
		flags = 0;	/* All guesses are wrong initially. */
		for (i = 0; i < 8 && len; i++) {
    			if (priv->GuessTable[priv->Hash] == *source)
				/* Guess was right - don't output. */
				flags |= (1 << i);
    			else {
				/* Guess wrong, output char. */
				priv->GuessTable[priv->Hash] = *source;
				*dest++ = *source;
    			}
    			HASH(*source++);
    			len--;
		}
		*flagdest = flags;
	}
	return (dest - orgdest);
}
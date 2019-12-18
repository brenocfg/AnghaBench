void sq_flush_range(unsigned long start, unsigned int len)
{
	unsigned long *sq = (unsigned long *)start;

	/* Flush the queues */
	for (len >>= 5; len--; sq += 8)
		prefetchw(sq);

	/* Wait for completion */
	store_queue_barrier();
}